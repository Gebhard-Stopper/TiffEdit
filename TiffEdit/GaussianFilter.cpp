#include "stdafx.h"
#include "GaussianFilter.h"


CGaussianFilter::CGaussianFilter()
	: CFilterBase(_T("Gaussian Filter"))
{
}


CGaussianFilter::~CGaussianFilter()
{
}

void CGaussianFilter::_applyFilter(CRawImage *pImage) {}
void CGaussianFilter::_applyFilterRGBA(CRawImage *pImage) {}