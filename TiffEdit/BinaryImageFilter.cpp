#include "stdafx.h"
#include "BinaryImageFilter.h"


CBinaryImageFilter::CBinaryImageFilter()
	: CFilterBase(_T("Binary Filter"))
{
}


CBinaryImageFilter::~CBinaryImageFilter()
{
}


void CBinaryImageFilter::_applyFilter(CRawImage *pImage, const CFilterParam* pParams) {}