#pragma once
class CDIBSection
{
private:
	BITMAPINFOHEADER m_BmpHeader;
	HBITMAP  m_hBmp;
	void	*m_pBits;
	CSize	 m_Size;

public:
	CDIBSection(UINT nWidth, UINT nHeight, UINT nBPP);
	~CDIBSection();
};

