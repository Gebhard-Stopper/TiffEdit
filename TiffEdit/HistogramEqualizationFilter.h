#pragma once
#include "FilterBase.h"
class CHistogramEqualizationFilter :
	public CFilterBase
{
public:
	CHistogramEqualizationFilter();
	~CHistogramEqualizationFilter();

private:
	virtual void _applyFilter(CRawImage *pImage);
	virtual void _applyFilterRGBA(CRawImage *pImage);
};

