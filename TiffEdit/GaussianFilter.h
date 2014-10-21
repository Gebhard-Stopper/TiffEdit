#pragma once
#include "FilterBase.h"
class CGaussianFilter :
	public CFilterBase
{
public:
	CGaussianFilter();
	~CGaussianFilter();

private:
	virtual void _applyFilter(CRawImage *pImage);
	virtual void _applyFilterRGBA(CRawImage *pImage);
};

