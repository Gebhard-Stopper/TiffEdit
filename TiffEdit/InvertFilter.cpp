#include "stdafx.h"
#include "InvertFilter.h"


CInvertFilter::CInvertFilter()
	: CFilterBase(_T("Invert Filter"))
{
}


CInvertFilter::~CInvertFilter()
{
}

void CInvertFilter::_onApplyFilter(CRawImage *pImage, ColorChannel nChannel)
{
	auto pPxlBuff = pImage->GetBitmapBits();

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