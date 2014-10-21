#include "stdafx.h"
#include "DIBSection.h"


CDIBSection::CDIBSection(UINT nWidth, UINT nHeight, UINT nBPP)
{
	ASSERT(nWidth > 0 && nHeight > 0);
	ASSERT(nBPP == 8 || nBPP == 16 || nBPP == 24 || nBPP == 32);

	m_Size.SetSize(nWidth, nHeight);

	memset(&m_BmpHeader, NULL, sizeof(BITMAPINFOHEADER));

	m_BmpHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_BmpHeader.biWidth = ((((int)nWidth * 8) + 31) & ~31) >> 3;
	m_BmpHeader.biHeight = nHeight;
	m_BmpHeader.biPlanes = 1;
	m_BmpHeader.biBitCount = nBPP;
	m_BmpHeader.biCompression = BI_RGB;
}


CDIBSection::~CDIBSection()
{
}
