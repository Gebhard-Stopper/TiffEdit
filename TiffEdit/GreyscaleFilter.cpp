#include "stdafx.h"
#include "GreyscaleFilter.h"


CGreyscaleFilter::CGreyscaleFilter()
	: CFilterBase(_T("Greyscale Filter"))
{
}


CGreyscaleFilter::~CGreyscaleFilter()
{
}

void CGreyscaleFilter::_applyFilter(CRawImage *pImage) {}
void CGreyscaleFilter::_applyFilterRGBA(CRawImage *pImage) {}