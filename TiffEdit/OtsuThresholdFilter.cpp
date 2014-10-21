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

void COtsuThresholdFilter::_applyFilter(CRawImage *pImage) 
{
	CHistogram histo(CHistogram::Grey, 8);
	histo.ComputeHisogram(pImage);

	float otsu = histo.ComputeOtsuThreshold();

	float *pPxlBuff = static_cast<float*>(pImage->GetBitmapBits());

	int nHeight = pImage->Height();
	int nWidth = pImage->SamplesPerRow();

	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			if (pPxlBuff[y*nWidth + x] < otsu) {
				pPxlBuff[y*nWidth + x] = 0.0f;
			}
		}
	}
}
void COtsuThresholdFilter::_applyFilterRGBA(CRawImage *pImage) {}