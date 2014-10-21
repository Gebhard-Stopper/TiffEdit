#pragma once
#include "FilterBase.h"
class CDilationFilter :
	public CFilterBase
{
public:
	CDilationFilter();
	~CDilationFilter();

private:
	virtual void _applyFilter(CRawImage *pImage);
	virtual void _applyFilterRGBA(CRawImage *pImage);
};

