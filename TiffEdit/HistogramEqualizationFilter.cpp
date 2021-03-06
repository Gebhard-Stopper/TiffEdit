#include "stdafx.h"
#include "HistogramEqualizationFilter.h"
#include "Histogram.h"

CHistogramEqualizationFilter::CHistogramEqualizationFilter()
	:CFilterBase(_T("Hisogram equalization"))
{
}


CHistogramEqualizationFilter::~CHistogramEqualizationFilter()
{
}

void CHistogramEqualizationFilter::_onApplyFilter(CRawImage *pImage, const CFilterParam* pParams)
{
	CHistogram histo(pParams->nChannel, 16);
	histo.ComputeHisogram(pImage);

	histo.ToCumulativeHistogram();

	int nWidth = pImage->Width();
	int nHeight = pImage->Height();
	float pxlCount = static_cast<float>(nWidth * nHeight);

	auto pPixel = pImage->GetBitmapBits();
	int nMaxValue = histo.GetMaxValue();

	for (int y = 0; y < nHeight; ++y) 
	{
		for (int x = 0; x < nWidth; ++x) 
		{
			int indx = pPixel[y*nWidth + x][pParams->nChannel] * nMaxValue;
			pPixel[y*nWidth + x][pParams->nChannel] = (pPixel[y*nWidth + x][pParams->nChannel] + (histo[indx] / pxlCount)) / 2.0f;
		}
	}
}