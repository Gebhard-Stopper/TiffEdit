#pragma once
#include "FilterBase.h"

class GaussFilterParam
	: public CFilterParam
{
public:
	GaussFilterParam(ColorChannel nChannel, int kernelHalfSize, float sigma)
		: CFilterParam(nChannel), nKernelHalfSize(kernelHalfSize), fSigma(sigma)
	{}

public:
	int nKernelHalfSize;
	float fSigma;

public:
	virtual CString ToString() const;
};

class CGaussianFilter :
	public CFilterBase
{
public:
	CGaussianFilter();
	~CGaussianFilter();

private:
	virtual void _onApplyFilter(CRawImage *pImage, const CFilterParam* pParams);
	float* _getGaussKernel(int nKernelHalfSize, float fSigma);
};

