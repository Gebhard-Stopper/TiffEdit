#include "stdafx.h"
#include "Histogram.h"

CHistogram::CHistogram(ColorChannel colorChannel, UINT uBitsPerSample) //2 ^ uBitsPerSample = number of buckets
	:m_nColorChannel(colorChannel)
{
	m_nNumValues = static_cast<int>(pow(2.0, (double)uBitsPerSample));
	m_pBuckets = static_cast<float*>(calloc(m_nNumValues, sizeof(float)));
}

CHistogram::CHistogram(const CHistogram &src)
{
	m_nColorChannel = src.m_nColorChannel;
	m_nNumValues = src.m_nNumValues;
	m_nTotalPixelCount = src.m_nTotalPixelCount;
	m_pBuckets = static_cast<float*>(malloc(m_nNumValues * sizeof(float)));

	memcpy(m_pBuckets, src.m_pBuckets, m_nNumValues * sizeof(float));
}

CHistogram::~CHistogram()
{
	free(m_pBuckets);
}

void CHistogram::ComputeHisogram(CRawImage *pImage)
{
	m_nTotalPixelCount = pImage->Width() * pImage->Height();

	_computeHistogramRGB(pImage);
}

void CHistogram::_computeHistogramRGB(CRawImage *pImage)
{
	auto pPxlBuff = pImage->GetBitmapBits();

	int nHeight = pImage->Height();
	int nWidth = pImage->Width();
	int nMaxValue = m_nNumValues - 1;

	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			m_pBuckets[static_cast<int>(pPxlBuff[y*nWidth + x][m_nColorChannel] * nMaxValue)]++;
		}
	}
}

void CHistogram::Normalize()
{
	float fPixelCount = static_cast<float>(m_nTotalPixelCount);

	for (int i = 0; i < m_nNumValues; ++i)
	{
		m_pBuckets[i] /= fPixelCount;
	}	
}

float CHistogram::CalcMean() const
{
	float fMean = 0.0f;

	for (int i = 0; i < m_nNumValues; ++i)
	{
		fMean += (i*m_pBuckets[i]);
	}
		
	return fMean;
}

float CHistogram::CalcVariance() const
{
	float fVaricance = 0.0f;
	float fMean = CalcMean();

	for (int i = 0; i < m_nNumValues; ++i)
	{
		fVaricance += pow((i - fMean), 2.0f)*m_pBuckets[i];
	}

	return fVaricance;
}

void CHistogram::ToCumulativeHistogram()
{
	for (int i = 1; i < m_nNumValues; ++i) {
		m_pBuckets[i] += m_pBuckets[i - 1];
	}
}

float CHistogram::ComputeOtsuThreshold() const
{
	CHistogram dummy(*this);

	float sum = 0;
	for (int i = 0; i < m_nNumValues; ++i) {
		sum += i * dummy[i];
	}

	float sumB = 0;
	int wB = 0;
	int wF = 0;

	float varMax = 0;
	float threshold = 0;

	for (int t = 0; t < m_nNumValues; t++) {
		wB += dummy[t];               // Weight Background
		if (wB == 0) continue;

		wF = m_nTotalPixelCount - wB;                 // Weight Foreground
		if (wF == 0) break;

		sumB += (float)(t * dummy[t]);

		float mB = sumB / wB;            // Mean Background
		float mF = (sum - sumB) / wF;    // Mean Foreground

		// Calculate Between Class Variance
		float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);

		// Check if new maximum found
		if (varBetween > varMax) {
			varMax = varBetween;
			threshold = t;
		}
	}
	return threshold / m_nNumValues;
}