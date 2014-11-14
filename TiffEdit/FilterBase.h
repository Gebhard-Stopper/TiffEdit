#pragma once

#include "RawImage.h"

class CFilterParam
{
public:
	CFilterParam(ColorChannel channel)
		:nChannel(channel)
	{}

public:
	ColorChannel nChannel;

public:
	virtual CString ToString() const;
};

class CFilterBase
{
protected:
	CString m_strFiltername;

public:
	CFilterBase(const CString& strFilterName);
	~CFilterBase();

public:
	void ApplyFilter(CRawImage *pImage, const CFilterParam* pParams);

private:
	virtual void _onApplyFilter(CRawImage *pImage, const CFilterParam* pParams) = NULL;
};

