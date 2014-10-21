#include "stdafx.h"
#include "RawImage.h"

void CRawImage::Draw()
{

	switch (m_ImageInfo.m_nColorFormat)
	{
		case ColorFormat::GreysScale:
			_drawGreyscale();
			break;
		case ColorFormat::RGB:
			_drawRGB();
			break;
		case ColorFormat::RGBA:
			_drawRGBA();
			break;
	}	
}

void CRawImage::_drawGreyscale() const
{
	glBegin(GL_POINTS);

	for (int y = 0; y < m_ImageInfo.m_nHeight; ++y) {
		for (int x = 0; x < m_ImageInfo.m_nWidth; ++x) {
			float color = static_cast<float*>(m_pBits)[y*m_ImageInfo.m_nWidth + x];
			glColor3f(color, color, color);
			glVertex2d(x, y);
		}
	}

	glEnd();
}

void CRawImage::_drawRGB() const
{
	glBegin(GL_POINTS);

	int colorChannels = 3;
	int readWidth = m_ImageInfo.m_nWidth * sizeof(float);

	for (int y = 0; y < m_ImageInfo.m_nHeight; ++y) {
		for (int x = 0; x < m_ImageInfo.m_nWidth; ++x) {
			float *pColor = &static_cast<float*>(m_pBits)[y* readWidth + (x*colorChannels)];
			glColor3fv(pColor);
			glVertex2d(x, y);
		}
	}

	glEnd();
}

void CRawImage::_drawRGBA() const
{
	glBegin(GL_POINTS);

	int colorChannels = 4;
	int readWidth = m_ImageInfo.m_nWidth * sizeof(float);

	for (int y = 0; y < m_ImageInfo.m_nHeight; ++y) {
		for (int x = 0; x < m_ImageInfo.m_nWidth; ++x) {
			float *pColor = &static_cast<float*>(m_pBits)[y* readWidth + (x*colorChannels)];
			glColor4fv(pColor);
			glVertex2d(x, y);
		}
	}

	glEnd();
}

CRawImage* CRawImage::CreateCompatibleImage(const CRawImage* pSrc)
{
	return new CRawImage(pSrc->m_ImageInfo.m_nWidth, pSrc->m_ImageInfo.m_nHeight, pSrc->m_ImageInfo.m_nColorFormat);
}