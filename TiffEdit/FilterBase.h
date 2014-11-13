#pragma once

#include "RawImage.h"


class CFilterBase
{
protected:
	CString m_strFiltername;

public:
	CFilterBase(const CString& strFilterName);
	~CFilterBase();

public:
	void ApplyFilter(CRawImage *pImage, ColorChannel nChannel);

private:
	virtual void _onApplyFilter(CRawImage *pImage, ColorChannel nChannel) = NULL;
};

