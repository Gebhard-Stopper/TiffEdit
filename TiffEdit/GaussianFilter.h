#pragma once
#include "FilterBase.h"
class CGaussianFilter :
	public CFilterBase
{
public:
	CGaussianFilter();
	~CGaussianFilter();

private:
	virtual void _onApplyFilter(CRawImage *pImage, ColorChannel nChannel);
};

