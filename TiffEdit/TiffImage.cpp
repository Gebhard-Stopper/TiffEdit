#include "stdafx.h"
#include "TiffImage.h"
#include "Log.h"


CTiffImage::CTiffImage(TIFF *pTiffImage)
	: CImageBase(ImageContainerFormat::Tiff), m_pExtendedImageInfo(nullptr)
{
	ASSERT(pTiffImage);
	m_pTiffImage = pTiffImage;	

	_readImageInfo();

	m_nCurrentDirectory = 0;

	m_ImageStack.reserve(m_pExtendedImageInfo->m_nDirectoryCount);
	for (int i = 0; i < m_pExtendedImageInfo->m_nDirectoryCount; ++i)
	{
		m_ImageStack.push_back(nullptr);
	}	

	_ensureCurrentImageIsLoaded();

	CLog::Info(_T("TIFF image loaded. Size : %u x %u @%uBPP, Stack-size: %u"), m_ImageInfo.m_nWidth, m_ImageInfo.m_nHeight, m_ImageInfo.m_nBitsPerSample*m_ImageInfo.m_nColorFormat, m_pExtendedImageInfo->m_nDirectoryCount);
}

CTiffImage* CTiffImage::Open(const CString& filePath)
{
	CStringA strDummy(filePath);

	TIFF *pImage = TIFFOpen((LPCSTR)strDummy, "r");
	if (pImage)
	{
		return  new CTiffImage(pImage);
	}

	return nullptr;
}

CTiffImage::~CTiffImage()
{
	Close();
}

void CTiffImage::Close()
{
	if (m_pTiffImage)
	{
		TIFFClose(m_pTiffImage);
		m_pTiffImage = nullptr;
	}

	m_ImageStack.clear();
}

void CTiffImage::Draw() const
{
	m_ImageStack[m_nCurrentDirectory]->Draw();
}

BOOL CTiffImage::_readImage(CRawImage *pImage)
{
	switch (m_ImageInfo.m_nBitsPerSample)
	{
		case 8:
			_readScanlineImage8(pImage);
			break;
		case 16:
			_readScanlineImage16(pImage);
			break;
		case 32:
			_readScanlineImage32(pImage);
			break;
	}
	
	//return TIFFReadRGBAImage(m_pTiffImage, m_nWidth, m_nHeight, pBUffer, 0);
	return TRUE;
}

void CTiffImage::_readScanlineImage8(CRawImage *pImage)
{
	float *pPixelBuff = static_cast<float*>(pImage->GetBitmapBits());

	auto scanline = TIFFScanlineSize(m_pTiffImage);

	auto scanlineBuffer = _TIFFmalloc(scanline);

	float maxVal = pow(2, m_ImageInfo.m_nBitsPerSample) - 1;
	int pxlBuff;

	for (int row = 0; row < m_ImageInfo.m_nHeight; ++row)
	{
		TIFFReadScanline(m_pTiffImage, scanlineBuffer, row);
		for (int col = 0; col < scanline; ++col){
			*pPixelBuff = static_cast<BYTE*>(scanlineBuffer)[col] / maxVal;
			pPixelBuff++;
		}
	}

	_TIFFfree(scanlineBuffer);
}

void CTiffImage::_readScanlineImage16(CRawImage *pImage)
{
	float *pPixelBuff = static_cast<float*>(pImage->GetBitmapBits());

	auto scanline = TIFFScanlineSize(m_pTiffImage);
	auto scanlinePxls = scanline / (m_ImageInfo.m_nBitsPerSample / 8);

	auto scanlineBuffer = _TIFFmalloc(scanline);

	//float maxVal = pow(2, m_nBitsPerSample) - 1;
	int pxlBuff;

	float maxVal = 0.0f;

	for (int row = 0; row < m_ImageInfo.m_nHeight; ++row)
	{
		TIFFReadScanline(m_pTiffImage, scanlineBuffer, row);
		for (int col = 0; col < scanlinePxls; ++col){
			float color = (float) static_cast<UINT16*>(scanlineBuffer)[col];// / maxVal;
			if (color > maxVal) maxVal = color;
			/*color *= 100;
			if (color > 1.0f) color = 1.0f;*/
			*pPixelBuff = color;

			pPixelBuff++;
		}
	}

	pPixelBuff = static_cast<float*>(pImage->GetBitmapBits());

	for (int row = 0; row < m_ImageInfo.m_nHeight; ++row)
	{
		for (int col = 0; col < scanlinePxls; ++col){
			*(pPixelBuff++) = *pPixelBuff / maxVal;
		}
	}

	_TIFFfree(scanlineBuffer);
}

void CTiffImage::_readScanlineImage32(CRawImage *pImage)
{
	float *pPixelBuff = static_cast<float*>(pImage->GetBitmapBits());

	auto scanline = TIFFScanlineSize(m_pTiffImage);
	auto scanlinePxls = scanline / (m_ImageInfo.m_nBitsPerSample / 8);

	auto scanlineBuffer = _TIFFmalloc(scanline);

	float maxVal = pow(2, m_ImageInfo.m_nBitsPerSample) - 1;
	int pxlBuff;

	for (int row = 0; row < m_ImageInfo.m_nHeight; ++row)
	{
		TIFFReadScanline(m_pTiffImage, scanlineBuffer, row);
		for (int col = 0; col < scanlinePxls; ++col){
			*pPixelBuff = static_cast<UINT32*>(scanlineBuffer)[col] / maxVal;
			pPixelBuff++;
		}
	}

	_TIFFfree(scanlineBuffer);
}

void CTiffImage::NextDirectory()
{
	if (TIFFReadDirectory(m_pTiffImage)) {
		++m_nCurrentDirectory;
		_ensureCurrentImageIsLoaded();
	}	
}

void CTiffImage::PreviousDirectory()
{
	if (m_nCurrentDirectory > 0) {
		TIFFSetDirectory(m_pTiffImage, --m_nCurrentDirectory);
		_ensureCurrentImageIsLoaded();
	}	
}

void CTiffImage::FirstDirectory()
{
	if (TIFFSetDirectory(m_pTiffImage, 0)) {
		_ensureCurrentImageIsLoaded();
	}
}

void CTiffImage::LastDirectory()
{
	if (TIFFSetDirectory(m_pTiffImage, m_pExtendedImageInfo->m_nDirectoryCount - 1)) {
		_ensureCurrentImageIsLoaded();
	}
}

BOOL CTiffImage::_ensureCurrentImageIsLoaded()
{
	if (m_ImageStack[m_nCurrentDirectory] == nullptr)
	{
		ColorFormat cf = static_cast<ColorFormat>(m_ImageInfo.m_nColorFormat);
		if (cf < 1 || cf >= ColorFormat::Count) {
			return FALSE;
		}

		CRawImage *pImage = new CRawImage(m_ImageInfo.m_nWidth, m_ImageInfo.m_nHeight, cf);

		if (pImage)
		{
			if (!_readImage(pImage))
			{
				throw new exception("Could not read image data.");
			}		

			m_ImageStack[m_nCurrentDirectory] = shared_ptr<CRawImage>(pImage);
		}
	}	
}

void* CTiffImage::GetBitmapBits() const
{
	if (m_ImageStack[m_nCurrentDirectory]) {
		return m_ImageStack[m_nCurrentDirectory]->GetBitmapBits();
	}

	return nullptr;
}

CRawImage* CTiffImage::GetCurrentDirectory() const
{
	return m_ImageStack[m_nCurrentDirectory].get();
}

void CTiffImage::ApplyFilter(CFilterBase &filter)
{
	auto pImg = GetCurrentDirectory();
	if (pImg) {
		filter.ApplyFilter(pImg);
	}
}

void CTiffImage::_readImageInfo()
{
	ASSERT(m_pExtendedImageInfo == nullptr);

	TIFFGetField(m_pTiffImage, TIFFTAG_IMAGEWIDTH, &m_ImageInfo.m_nWidth);
	TIFFGetField(m_pTiffImage, TIFFTAG_IMAGELENGTH, &m_ImageInfo.m_nHeight);
	TIFFGetField(m_pTiffImage, TIFFTAG_BITSPERSAMPLE, &m_ImageInfo.m_nBitsPerSample);
	TIFFGetField(m_pTiffImage, TIFFTAG_SAMPLESPERPIXEL, &m_ImageInfo.m_nColorFormat);

	m_pExtendedImageInfo = new CTiffImageInfo;
	m_ImageInfo.SetExtendedImageInfo(m_pExtendedImageInfo);

	m_pExtendedImageInfo->m_nDirectoryCount = TIFFNumberOfDirectories(m_pTiffImage);	//Number of images in image stack

	if (!TIFFGetFieldDefaulted(m_pTiffImage, TIFFTAG_COMPRESSION, &m_pExtendedImageInfo->m_nCompression)) {
		m_pExtendedImageInfo->m_nCompression = 1;
	}

	if (!TIFFGetFieldDefaulted(m_pTiffImage, TIFFTAG_XRESOLUTION, &m_pExtendedImageInfo->m_nXResolution)) {
		m_pExtendedImageInfo->m_nXResolution = 0;
	}

	if (!TIFFGetFieldDefaulted(m_pTiffImage, TIFFTAG_YRESOLUTION, &m_pExtendedImageInfo->m_nYResolution)) {
		m_pExtendedImageInfo->m_nYResolution = 0;
	}

	if (!TIFFGetFieldDefaulted(m_pTiffImage, TIFFTAG_RESOLUTIONUNIT, &m_pExtendedImageInfo->m_nResolutionUnit)) {
		m_pExtendedImageInfo->m_nResolutionUnit = RESUNIT_NONE;
	}
	
	char* pBuffer;

	if (TIFFGetFieldDefaulted(m_pTiffImage, TIFFTAG_SOFTWARE, &pBuffer)) {
		m_pExtendedImageInfo->m_strSoftware = CString(pBuffer);
	}

	if (TIFFGetFieldDefaulted(m_pTiffImage, TIFFTAG_DATETIME, &pBuffer)) {
		m_pExtendedImageInfo->m_dtCreated.ParseDateTime(CString(pBuffer));
	}

	if (TIFFGetFieldDefaulted(m_pTiffImage, TIFFTAG_ARTIST, &pBuffer)) {
		m_pExtendedImageInfo->m_strArtist = CString(pBuffer);
	}

	if (TIFFGetFieldDefaulted(m_pTiffImage, TIFFTAG_HOSTCOMPUTER, &pBuffer)) {
		m_pExtendedImageInfo->m_strHostName = CString(pBuffer);
	}

	if (TIFFGetFieldDefaulted(m_pTiffImage, TIFFTAG_COPYRIGHT, &pBuffer)) {
		m_pExtendedImageInfo->m_strCopyright = CString(pBuffer);
	}

	if (TIFFGetFieldDefaulted(m_pTiffImage, TIFFTAG_IMAGEDESCRIPTION, &pBuffer)) {
		m_pExtendedImageInfo->m_strDescription = CString(pBuffer);
	}
}