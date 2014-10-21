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
	void ApplyFilter(CRawImage *pImage);

private:
	virtual void _onApplyFilter(CRawImage *pImage);
	virtual void _applyFilter(CRawImage *pImage) = NULL;
	virtual void _applyFilterRGBA(CRawImage *pImage) = NULL;
};

