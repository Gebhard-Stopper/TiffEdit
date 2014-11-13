#pragma once
#include "FilterBase.h"
class CInvertFilter :
	public CFilterBase
{
public:
	CInvertFilter();
	~CInvertFilter();

private:
	virtual void _onApplyFilter(CRawImage *pImage, ColorChannel nChannel);
};

