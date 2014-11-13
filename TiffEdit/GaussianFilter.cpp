#include "stdafx.h"
#include "GaussianFilter.h"


CGaussianFilter::CGaussianFilter()
	: CFilterBase(_T("Gaussian Filter"))
{
}


CGaussianFilter::~CGaussianFilter()
{
}

void CGaussianFilter::_onApplyFilter(CRawImage *pImage, ColorChannel nChannel)
{

}