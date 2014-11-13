#pragma once
#include "RawImage.h"

class CHistogram
{
private:
	ColorChannel	 m_nColorChannel;
	float			*m_pBuckets;
	int				 m_nNumValues;
	int				 m_nTotalPixelCount;

public:
	CHistogram(ColorChannel colorChannel, UINT uBitsPerSample); //2 ^ uBitsPerSample = number of buckets
	CHistogram(const CHistogram &src);
	~CHistogram();

public:
	void ComputeHisogram(CRawImage *pImage);
	void Normalize();
	void ToCumulativeHistogram();

	float CalcMean() const;
	float CalcVariance() const;
	float ComputeOtsuThreshold() const;

	int GetMaxValue() const  { return m_nNumValues - 1; }

public:
	float& operator [] (int nIndx) { return m_pBuckets[nIndx]; }

private:
	void _computeHistogramRGB(CRawImage *pImage);
};

