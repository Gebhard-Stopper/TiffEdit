#pragma once
#include "FilterBase.h"

class COtsuThresholdFilter :
	public CFilterBase
{
public:
	COtsuThresholdFilter();
	~COtsuThresholdFilter();

private:
	virtual void _onApplyFilter(CRawImage *pImage, const CFilterParam* pParams);
};

