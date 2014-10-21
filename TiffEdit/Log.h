#pragma once
#include <vector>
#include "LogWriter.h"

using namespace std;

class CLog
{
private:
	static vector<shared_ptr<CLogWriter>> m_LogWriter;

public:
	CLog();
	~CLog();

public:
	static void AppendLogWriter(CLogWriter *pLogWriter);
	static void InitWriters();

public:
	static void Error(const CString& format, ...);
	static void Error(CException *pException, const CString& format, ...);
	static void Warning(const CString& format, ...);
	static void Warning(CException *pException, const CString& format, ...);
	static void Info(const CString& format, ...);
	static void Info(CException *pException, const CString& format, ...);
	static void Debug(const CString& format, ...);
	static void Debug(CException *pException, const CString& format, ...);

private:
	static void _createLogMessage(MessageSeverity nSeverity, CException *pException, const CString& format, va_list args);
	static void _enqueueMessage(CLogMessage* pMessage);
};

