#pragma once

enum MessageSeverity { Debug, Info, Warning, Error };

class CLogMessage
{
public:
	CLogMessage(MessageSeverity nSeverity, CException *pException, const CString strLogMessage);

private:
	MessageSeverity	m_nSeverity;
	CString			m_strException;
	CString			m_strLogMessage;
	COleDateTime	m_TimeStamp;

public:
	CString ToString() const;
};