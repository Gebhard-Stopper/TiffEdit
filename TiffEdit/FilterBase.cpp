#include "stdafx.h"
#include "FilterBase.h"
#include "Log.h"

CString CFilterParam::ToString() const
{
	CString strChannelName;

	switch (nChannel)
	{
	case ColorChannel::Hue:
		strChannelName = _T("Hue");
		break;
	case ColorChannel::Saturation:
		strChannelName = _T("Saturation");
		break;
	case ColorChannel::Value:
		strChannelName = _T("Value");
		break;
	case ColorChannel::Alpha:
		strChannelName = _T("Alpha");
			break;
	default:
		strChannelName = _T("Unknown Channel");
		break;
	}

	return _T("Operating on Channel: " + strChannelName);
}

CFilterBase::CFilterBase(const CString& strFilterName)
	:m_strFiltername(strFilterName)
{
}

CFilterBase::~CFilterBase()
{
}

void CFilterBase::ApplyFilter(CRawImage *pImage, const CFilterParam* pParams)
{
	CLog::Info(_T("Applying %s. %s"), m_strFiltername, pParams->ToString());

	_onApplyFilter(pImage, pParams);
}