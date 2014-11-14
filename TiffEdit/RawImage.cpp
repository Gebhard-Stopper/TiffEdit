#include "stdafx.h"
#include "RawImage.h"
#include "ColorConv.h"
void CRawImage::Draw()
{
	auto pPxl = static_cast<Pixelf*>(m_pBits);

	glBegin(GL_POINTS);

	Pixelf dummy;

	for (int y = 0; y < m_ImageInfo.m_nHeight; ++y) 
	{
		for (int x = 0; x < m_ImageInfo.m_nWidth; ++x) 
		{
#ifdef USE_HSV
			ColorConverter::ConvertToRGB(&(pPxl[y*m_ImageInfo.m_nWidth + x]), &dummy);
			glColor4fv(reinterpret_cast<float*>(&dummy));
#else
			glColor4fv(reinterpret_cast<float*>(&(pPxl[y*m_ImageInfo.m_nWidth + x])));
#endif
			glVertex2d(x, y);
		}
	}

	glEnd();
}

CRawImage* CRawImage::CreateCompatibleImage(const CRawImage* pSrc)
{
	return new CRawImage(pSrc->m_ImageInfo.m_nWidth, pSrc->m_ImageInfo.m_nHeight, pSrc->m_ImageInfo.m_nColorFormat);
}