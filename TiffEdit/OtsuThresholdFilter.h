#pragma once
#include "FilterBase.h"

class COtsuThresholdFilter :
	public CFilterBase
{
public:
	COtsuThresholdFilter();
	~COtsuThresholdFilter();

private:
	virtual void _applyFilter(CRawImage *pImage);
	virtual void _applyFilterRGBA(CRawImage *pImage);
};

