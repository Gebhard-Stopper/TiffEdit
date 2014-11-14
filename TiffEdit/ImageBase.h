#pragma once
#include "FilterBase.h"

class CImageBase
{
public:
	enum ImageContainerFormat { Tiff, Jpeg, Png, Gif, Bmp};

protected:
	ImageContainerFormat	m_nImageContainer;
	CImageInfo	m_ImageInfo;

public:
	virtual void* GetBitmapBits() const = NULL;
	virtual void Draw() const = NULL;
	virtual void ApplyFilter(CFilterBase &filter, const CFilterParam* pParams) = NULL;

public:
	CImageBase(ImageContainerFormat nImageContainer);
	virtual ~CImageBase() = NULL;

public:
	__inline UINT Width() const { return m_ImageInfo.m_nWidth; }
	__inline UINT Height() const { return m_ImageInfo.m_nHeight; }
	__inline UINT SamplesPerRow() const { return m_ImageInfo.m_nWidth * m_ImageInfo.m_nColorFormat; }
	__inline UINT BitsPerPixel() const { return m_ImageInfo.m_nBitsPerSample * m_ImageInfo.m_nColorFormat; }
	__inline ImageContainerFormat GetImageContainerFormat() const { return m_nImageContainer; }
	__inline const CImageInfo* GetImageInfo() const { return const_cast<CImageInfo *>(&m_ImageInfo); }
};

