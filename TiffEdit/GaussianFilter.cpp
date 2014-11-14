#include "stdafx.h"
#include "GaussianFilter.h"
#include "ColorConv.h"

#define _USE_MATH_DEFINES 
#include <math.h>


CString GaussFilterParam::ToString() const
{
	CString strDummy;
	strDummy.Format(_T("Kernel-size: %d, Sigma: %f"), nKernelHalfSize, fSigma);

	return strDummy;
}

CGaussianFilter::CGaussianFilter()
	: CFilterBase(_T("Gaussian Filter"))
{
}

CGaussianFilter::~CGaussianFilter()
{
}

void CGaussianFilter::_onApplyFilter(CRawImage *pImage, const CFilterParam* pParams)
{
	auto params = static_cast<const GaussFilterParam*>(pParams);

	int nWidth = pImage->Width();
	int nHeight = pImage->Height();

	CRawImage dummy(nHeight, nWidth, pImage->GetColorFormat());

	ColorConverter::ConvertToRGB(pImage);
	
	auto pPixel = pImage->GetBitmapBits();
	auto pDummyPixel = dummy.GetBitmapBits();

	float *pKernel = _getGaussKernel(params->nKernelHalfSize, params->fSigma);

	//Step One, convolve in x
	for (int j = 0; j < nHeight; ++j)
	{
		for (int i = 0; i < nWidth; ++i)
		{
			Pixelf sum(0.0f);

			//Loop over kernel
			for (int k = -params->nKernelHalfSize; k <= params->nKernelHalfSize; ++k)
			{
				//enforces a black boundary
				if (i + k > -1 && i + k < nWidth) // ( j >= 0 && j < m_nSamplesY) // implicitly given
				{
					sum += pPixel[j*nWidth + i + k] * pKernel[k + params->nKernelHalfSize];
				}
			}	

			//Automatically rotate
			pDummyPixel[i*nHeight + j] = sum;
		}
	}

	//Setp 2, convolve in y
	for (int j = 0; j < nWidth; ++j)
	{
		for (int i = 0; i < nHeight; ++i)
		{
			Pixelf sum(0.0f);

			//Loop over kernel
			for (int k = -params->nKernelHalfSize; k <= params->nKernelHalfSize; ++k)
			{
				//enforces a black boundary
				if (i + k > -1 && i + k < nHeight) // ( j >= 0 && j < m_nSamplesY) // implicitly given
				{
					sum += pDummyPixel[j*nHeight + i + k] * pKernel[k + params->nKernelHalfSize];
				}
			}

			//Automatically rotate back to original position
			pPixel[i*nWidth + j] = sum;
		}
	}

	ColorConverter::ConvertToHSV(pImage);

	delete pKernel;
}

float* CGaussianFilter::_getGaussKernel(int nKernelHalfSize, float fSigma)
{
	int kSize = 2 * nKernelHalfSize + 1;
	float *pKernel = new float[kSize];

	//fill with values
	float sum = 0.0f;

	for (int k = -nKernelHalfSize; k <= nKernelHalfSize; k++)
	{
		pKernel[k + nKernelHalfSize] = static_cast<float>((((1.0 / (sqrt(2.0*M_PI)*fSigma))*(exp(-(float)(k*k) / (2.0*fSigma*fSigma))))));
		sum += pKernel[k + nKernelHalfSize];
	}

	//Normalize
	for (int i = 0; i < kSize; i++)
	{
		pKernel[i] /= sum;
	}
	
	return pKernel;
}