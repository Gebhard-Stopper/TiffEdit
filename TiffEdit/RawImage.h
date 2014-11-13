#pragma once
#include "ImageInfo.h"
#include "PixelDef.h"

class CRawImage
{
private:
	CImageInfo	 m_ImageInfo;
	void		*m_pBits; 

public:
	CRawImage(int nWidth, int nHeight, ColorFormat nColorFormat)
		: m_ImageInfo(nWidth, nHeight, 8 * sizeof(float), nColorFormat)
	{
		ASSERT(	m_ImageInfo.m_nColorFormat == ColorFormat::GreysScale || 
				m_ImageInfo.m_nColorFormat == ColorFormat::RGB || 
				m_ImageInfo.m_nColorFormat == ColorFormat::RGBA);

		m_pBits = malloc(m_ImageInfo.TotalPixelCount() * sizeof(Pixelf));
	}

	~CRawImage()
	{
		if (m_pBits) {
			free(m_pBits);
		}
	}

public:
	__inline int Width() const { return m_ImageInfo.m_nWidth; }
	__inline int Height() const { return m_ImageInfo.m_nHeight; }
	__inline int BitsPerPixel() const { return m_ImageInfo.m_nColorFormat * 8; }
	__inline Pixelf* GetBitmapBits() const { return static_cast<Pixelf*>(m_pBits); }
	__inline UINT SamplesPerRow() const { return m_ImageInfo.m_nWidth * m_ImageInfo.m_nColorFormat; }
	__inline ColorFormat GetColorFormat() const { return m_ImageInfo.m_nColorFormat; }

	__inline void Attach(void *pBits) { 
		if (m_pBits) 
			free(m_pBits);
		m_pBits = pBits; 
	}

	__inline void* Detach() {
		void *pDummy = m_pBits;
		m_pBits = nullptr;

		return pDummy;
	}

public:
	static CRawImage *CreateCompatibleImage(const CRawImage* pSrc);
	void Draw();
};

