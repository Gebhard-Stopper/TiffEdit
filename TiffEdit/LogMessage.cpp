#include "stdafx.h"
#include "LogMessage.h"


CLogMessage::CLogMessage(MessageSeverity nSeverity, CException *pException, const CString strLogMessage)
	:m_TimeStamp(COleDateTime::GetCurrentTime()), m_nSeverity(nSeverity), m_strLogMessage(strLogMessage)
{
	static TCHAR szException[4096];
	if (pException) {
		pException->GetErrorMessage(szException, sizeof(szException));
		m_strException = szException;
	}
}

CString CLogMessage::ToString() const
{
	CString strMsg;
	CString strSeverity;

	switch (m_nSeverity)
	{
	case MessageSeverity::Debug:
		strSeverity = _T("Debug");
		break;
	case MessageSeverity::Info:
		strSeverity = _T("Info");
		break;
	case MessageSeverity::Warning:
		strSeverity = _T("Warning");
		break;
	case MessageSeverity::Error:
		strSeverity = _T("Error");
		break;
	default:
		strSeverity = _T("Message");
		break;
	}

	strMsg.Format(_T("%s [%s]: %s\n%s"),	m_TimeStamp.Format(_T("%d.%m.%Y %H:%M:%S")),
											strSeverity,
											m_strLogMessage,
											m_strException);

	return strMsg;
}