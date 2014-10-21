#pragma once
#include "FilterBase.h"
class CInvertFilter :
	public CFilterBase
{
public:
	CInvertFilter();
	~CInvertFilter();

private:
	virtual void _applyFilter(CRawImage *pImage);
	virtual void _applyFilterRGBA(CRawImage *pImage);
};

