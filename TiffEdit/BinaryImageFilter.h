#pragma once
#include "FilterBase.h"

/**
	Creates a binary (black and white) image, based on the input image
*/
class CBinaryImageFilter :
	public CFilterBase
{
public:
	CBinaryImageFilter();
	~CBinaryImageFilter();

private:
	virtual void _applyFilter(CRawImage *pImage) ;
	virtual void _applyFilterRGBA(CRawImage *pImage) ;
};

