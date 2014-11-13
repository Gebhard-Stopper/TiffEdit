#pragma once
#include <memory>
#include <vector>
#include "tiffio.h" 
#include "ImageBase.h"
#include "RawImage.h"

using namespace std;

class CTiffImageInfo
	: public CExtendedImageInfo
{
public:
	int16   m_nDirectoryCount;
	int16	m_nCompression;

	/*
	*	It is not mandatory that the image be actually displayed or printed at the size implied by this parameter. 
	*	It is up to the application to use this information as it wishes.
	*/
	int16	m_nXResolution;		/**< The number of pixels per ResolutionUnit in the ImageWidth direction.*/
	int16	m_nYResolution;		/**< The number of pixels per ResolutionUnit in the ImageHeight direction.*/
	int16	m_nResolutionUnit;	/**< The unit of measurement for XResolution and YResolution. (None, Inche, Centimerter)*/

	CString	m_strSoftware;		/**< Name and version number of the software package(s) used to create the image.*/
	CString	m_strArtist;		/**< Person who created the image. Note: some older TIFF files used this tag for storing Copyright information.*/
	CString m_strHostName;		/**< The computer and/or operating system in use at the time of image creation.*/
	CString m_strCopyright;		/**< Copyright notice of the person or organization that claims the copyright to the image.*/
	CString m_strDescription;	/**< A string that describes the subject of the image.*/

	COleDateTime m_dtCreated;	/**< Date and time of image creation.*/
};

class CTiffImage 
	: public CImageBase
{
private:
	TIFF *m_pTiffImage;
	CTiffImageInfo	*m_pExtendedImageInfo;	/**< Do not delete the data pointed to by this pointer!*/

	int16	m_nCurrentDirectory;

	vector<shared_ptr<CRawImage>> m_ImageStack;

private:
	CTiffImage(TIFF *pTiffImage);

public:
	static CTiffImage* Open(const CString& filePath);
	~CTiffImage();

private:
	BOOL _readImage(CRawImage *pImage);

	template <class T>
	void _readScanlineImage(CRawImage *pImage);
	void _readScanlineImage8(CRawImage *pImage);
	void _readScanlineImage16(CRawImage *pImage);
	void _readScanlineImage32(CRawImage *pImage);

	BOOL _ensureCurrentImageIsLoaded();

	void _readImageInfo();

public:
	virtual void ApplyFilter(CFilterBase &filter, ColorChannel nColorChannel);

	virtual void* GetBitmapBits() const;

	void Close();
	virtual void Draw() const;

	CRawImage* GetCurrentDirectory() const;

	void NextDirectory();
	void PreviousDirectory();
	void FirstDirectory();
	void LastDirectory();
};

