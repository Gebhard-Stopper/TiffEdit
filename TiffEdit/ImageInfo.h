#pragma once

enum ColorFormat { None = 0x0, GreysScale = 0x01, RGB = 0x03, RGBA = 0x04 , Count = 0x5};

/**
 * Dummy class to hold data, speciffic to a certain image format.
 */
class CExtendedImageInfo
{
public:
	virtual ~CExtendedImageInfo() = NULL {};
};

class CImageInfo
{
public:
	int				m_nWidth;			/**< Width in pixel*/
	int				m_nHeight;			/**< Height in pixel*/
	int				m_nBitsPerSample;	/**< Bits per Sample. Multiplied with m_nColorFormat equals the number of bits per pixel.*/
	ColorFormat		m_nColorFormat;		/**< Number of samples (color channels) per pixel*/

private:
	CExtendedImageInfo	*m_pFormatSpecifficData;


public:
	CImageInfo(int nWidth, int nHeight, ColorFormat nColorFormat) 
		:	m_nWidth(nWidth), m_nHeight(nHeight), m_nColorFormat(nColorFormat), 
			m_pFormatSpecifficData(nullptr)
	{}

	CImageInfo(int nWidth, int nHeight, int nBitsPerSample, ColorFormat nColorFormat)
		:	m_nWidth(nWidth), m_nHeight(nHeight), m_nBitsPerSample(nBitsPerSample), m_nColorFormat(nColorFormat),
			m_pFormatSpecifficData(nullptr)
	{}

	~CImageInfo() {
		if (m_pFormatSpecifficData) {
			delete m_pFormatSpecifficData;
		}
	}

protected:
	CImageInfo()
		:	m_pFormatSpecifficData(nullptr)
	{}

public:
	__inline UINT TotalPixelCount() const { return m_nWidth * m_nHeight; }
	__inline CExtendedImageInfo* GetExtendedImageInfo() const { return m_pFormatSpecifficData; }
	__inline void SetExtendedImageInfo(CExtendedImageInfo *pFormatSpecifficData) { m_pFormatSpecifficData = pFormatSpecifficData; }

	friend class CImageBase;
};

