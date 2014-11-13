#pragma once
#include "FilterBase.h"
class CErosionFilter :
	public CFilterBase
{
public:
	CErosionFilter();
	~CErosionFilter();

private:
	virtual void _onApplyFilter(CRawImage *pImage, ColorChannel nChannel);
};

