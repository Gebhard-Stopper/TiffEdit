#include "stdafx.h"
#include "InvertFilter.h"


CInvertFilter::CInvertFilter()
	: CFilterBase(_T("Invert Filter"))
{
}


CInvertFilter::~CInvertFilter()
{
}

void CInvertFilter::_applyFilter(CRawImage *pImage)
{
	float *pPxlBuff = static_cast<float*>(pImage->GetBitmapBits());

	int nHeight = pImage->Height();
	int nWidth = pImage->SamplesPerRow();

	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x )
		{
			pPxlBuff[y*nWidth + x] = 1.0f - pPxlBuff[y*nWidth + x];
		}
	}
}

void CInvertFilter::_applyFilterRGBA(CRawImage *pImage)
{
	float *pPxlBuff = static_cast<float*>(pImage->GetBitmapBits());

	int nHeight = pImage->Height();
	int nWidth = pImage->SamplesPerRow();

	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; x += 4)
		{
			pPxlBuff[y*nWidth + x] = 1.0f - pPxlBuff[y*nWidth + x];
			pPxlBuff[y*nWidth + x+1] = 1.0f - pPxlBuff[y*nWidth + x+1];
			pPxlBuff[y*nWidth + x+2] = 1.0f - pPxlBuff[y*nWidth + x+2];
		}
	}
}