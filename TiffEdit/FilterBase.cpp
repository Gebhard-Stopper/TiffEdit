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

void CFilterBase::ApplyFilter(CRawImage *pImage) 
{
	CLog::Info(_T("Applying %s"), m_strFiltername);

	_onApplyFilter(pImage);
}

void CFilterBase::_onApplyFilter(CRawImage *pImage)
{
	switch (pImage->GetColorFormat())
	{
	case  ColorFormat::RGBA:
		_applyFilterRGBA(pImage);
		break;
	default:
		_applyFilter(pImage);
		break;
	}
}