#include "stdafx.h"
#include "FilterBase.h"
#include "Log.h"

CFilterBase::CFilterBase(const CString& strFilterName)
	:m_strFiltername(strFilterName)
{
}


CFilterBase::~CFilterBase()
{
}

void CFilterBase::ApplyFilter(CRawImage *pImage, ColorChannel nChannel)
{
	CLog::Info(_T("Applying %s"), m_strFiltername);

	_onApplyFilter(pImage, nChannel);
}