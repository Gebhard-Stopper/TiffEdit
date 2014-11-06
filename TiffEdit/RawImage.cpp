#include "stdafx.h"
#include "RawImage.h"
#include "ColorConv.h"
void CRawImage::Draw()
{
	auto pPxl = static_cast<Pixelf*>(m_pBits);

	glBegin(GL_POINTS);

	Pixelf dummy;

	for (int y = 0; y < m_ImageInfo.m_nHeight; ++y) {
		for (int x = 0; x < m_ImageInfo.m_nWidth; ++x) {
			ColorConverter::ConvertToRGB(&(pPxl[y*m_ImageInfo.m_nWidth + x]), &dummy);
			glColor4fv(reinterpret_cast<float*>(&dummy));
			glVertex2d(x, y);
		}
	}

	glEnd();
}

void CRawImage::_drawGreyscale() const
{
	auto pPxl = static_cast<Pixelf*>(m_pBits);

	glBegin(GL_POINTS);

	for (int y = 0; y < m_ImageInfo.m_nHeight; ++y) {
		for (int x = 0; x < m_ImageInfo.m_nWidth; ++x) {
			glColor3fv(reinterpret_cast<float*>(&pPxl[y*m_ImageInfo.m_nWidth + x]));
			glVertex2d(x, y);
		}
	}

	glEnd();
}

void CRawImage::_drawRGB() const
{
	glBegin(GL_POINTS);

	int colorChannels = 3;
	int realWidth = m_ImageInfo.m_nWidth * sizeof(float);

	for (int y = 0; y < m_ImageInfo.m_nHeight; ++y) {
		for (int x = 0; x < m_ImageInfo.m_nWidth; ++x) {
			float *pColor = &static_cast<float*>(m_pBits)[y* realWidth + (x*colorChannels)];
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