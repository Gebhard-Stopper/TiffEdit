#include "stdafx.h"
#include "OtsuThresholdFilter.h"
#include "Histogram.h"

COtsuThresholdFilter::COtsuThresholdFilter()
	: CFilterBase(_T("Otsu Threshold Filter"))
{
}


COtsuThresholdFilter::~COtsuThresholdFilter()
{
}

void COtsuThresholdFilter::_onApplyFilter(CRawImage *pImage, const CFilterParam* pParams)
{
	CHistogram histo(pParams->nChannel, 8);
	histo.ComputeHisogram(pImage);

	float otsu = histo.ComputeOtsuThreshold();

	auto pPxlBuff = pImage->GetBitmapBits();

	int nHeight = pImage->Height();
	int nWidth = pImage->Width();

	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			if (pPxlBuff[y*nWidth + x][pParams->nChannel] < otsu) 
			{
				pPxlBuff[y*nWidth + x][pParams->nChannel] = 0.0f;
			}
		}
	}
}