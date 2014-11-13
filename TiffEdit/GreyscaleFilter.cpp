#include "stdafx.h"
#include "GreyscaleFilter.h"


CGreyscaleFilter::CGreyscaleFilter()
	: CFilterBase(_T("Greyscale Filter"))
{
}


CGreyscaleFilter::~CGreyscaleFilter()
{
}

void CGreyscaleFilter::_onApplyFilter(CRawImage *pImage, ColorChannel nChannel)
{

}