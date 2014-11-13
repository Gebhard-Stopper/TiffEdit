#pragma once
#include "FilterBase.h"
class CGreyscaleFilter :
	public CFilterBase
{
public:
	CGreyscaleFilter();
	~CGreyscaleFilter();

private:
	virtual void _onApplyFilter(CRawImage *pImage, ColorChannel nChannel);
};

