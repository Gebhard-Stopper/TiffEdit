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

void CHistogramEqualizationFilter::_applyFilter(CRawImage *pImage) 
{
	CHistogram histo(CHistogram::Grey, 8);
	histo.ComputeHisogram(pImage);

	histo.ToCumulativeHistogram();

	int nWidth = pImage->Width();
	int nHeight = pImage->Height();
	float pxlCount = static_cast<float>(nWidth * nHeight);

	float *pPixel = static_cast<float*>(pImage->GetBitmapBits());
	int nMaxValue = histo.GetMaxValue();

	for (int y = 0; y < nHeight; ++y) {
		for (int x = 0; x < nWidth; ++x) {
			int indx = pPixel[y*nWidth + x] * nMaxValue;
			pPixel[y*nWidth + x] = (pPixel[y*nWidth + x] + (histo[indx] / pxlCount)) / 2.0f;
		}
	}
}
void CHistogramEqualizationFilter::_applyFilterRGBA(CRawImage *pImage) {}