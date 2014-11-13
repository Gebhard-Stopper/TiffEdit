#pragma once
#include "FilterBase.h"
class CHistogramEqualizationFilter :
	public CFilterBase
{
public:
	CHistogramEqualizationFilter();
	~CHistogramEqualizationFilter();

private:
	virtual void _onApplyFilter(CRawImage *pImage, ColorChannel nChannel);
};

