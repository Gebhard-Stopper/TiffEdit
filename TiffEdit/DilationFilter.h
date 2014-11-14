#pragma once
#include "FilterBase.h"
class CDilationFilter :
	public CFilterBase
{
public:
	CDilationFilter();
	~CDilationFilter();

private:
	virtual void _onApplyFilter(CRawImage *pImage, const CFilterParam* pParams);
};

