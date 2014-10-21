#pragma once
#include "FilterBase.h"
class CGreyscaleFilter :
	public CFilterBase
{
public:
	CGreyscaleFilter();
	~CGreyscaleFilter();

private:
	virtual void _applyFilter(CRawImage *pImage);
	virtual void _applyFilterRGBA(CRawImage *pImage);
};

