#pragma once
#include "FilterBase.h"
class CErosionFilter :
	public CFilterBase
{
public:
	CErosionFilter();
	~CErosionFilter();

private:
	virtual void _applyFilter(CRawImage *pImage);
	virtual void _applyFilterRGBA(CRawImage *pImage);
};

