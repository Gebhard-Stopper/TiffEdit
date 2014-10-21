#include "stdafx.h"
#include "Log.h"

#ifdef va_start
#undef va_start

#ifdef _WIN32
#define va_start(ap,v){int var=_INTSIZEOF(v);\
  __asm lea eax,v __asm add eax,var \
   __asm mov ap,eax  \
	    }
#else
#define va_start(ap,v){int var=_INTSIZEOF(v);\ 
__asm lea ax, v __asm add ax, var \
__asm mov ap, ax\
	}
#endif
#endif

vector<shared_ptr<CLogWriter>> CLog::m_LogWriter = vector<shared_ptr<CLogWriter>>();

CLog::CLog()
{
}

CLog::~CLog()
{
}

void CLog::Error(const CString& format, ...)
{
	va_list args;
	va_start(args, format);
	_createLogMessage(MessageSeverity::Error, nullptr, format, args);
	va_end(args);
}

void CLog::Error(CException *pException, const CString& format, ...)
{
	va_list args;
	va_start(args, format);
	_createLogMessage(MessageSeverity::Error, pException, format, args);
	va_end(args);
}

void CLog::Warning(const CString& format, ...)
{
	va_list args;
	va_start(args, format);
	_createLogMessage(MessageSeverity::Warning, nullptr, format, args);
	va_end(args);
}

void CLog::Warning(CException *pException, const CString& format, ...)
{
	va_list args;
	va_start(args, format);
	_createLogMessage(MessageSeverity::Warning, pException, format, args);
	va_end(args);
}

void CLog::Info(const CString& format, ...)
{
	va_list args;
	va_start(args, format);
	_createLogMessage(MessageSeverity::Info, nullptr, format, args);
	va_end(args);
}

void CLog::Info(CException *pException, const CString& format, ...)
{
	va_list args;
	va_start(args, format);
	_createLogMessage(MessageSeverity::Info, pException, format, args);
	va_end(args);
}

void CLog::Debug(const CString& format, ...)
{
#ifdef DEBUG 
	va_list args;
	va_start(args, format);
	_createLogMessage(MessageSeverity::Debug, nullptr, format, args);
	va_end(args);
#endif
}

void CLog::Debug(CException *pException, const CString& format, ...)
{
#ifdef DEBUG 
	va_list args;
	va_start(args, format);
	_createLogMessage(MessageSeverity::Debug, pException, format, args);
	va_end(args);
#endif
}

void CLog::_createLogMessage(MessageSeverity nSeverity, CException *pException, const CString& format, va_list args)
{
	CString strMessage;
	strMessage.FormatV(format, args);

	_enqueueMessage(new CLogMessage(nSeverity,
									pException,
									strMessage));
}

void CLog::_enqueueMessage(CLogMessage* pMessage)
{
	shared_ptr<CLogMessage> msg(pMessage);

	for (auto logWriter : m_LogWriter)
	{
		logWriter->Enqueue(msg);
	}
}


void CLog::AppendLogWriter(CLogWriter *pLogWriter)
{
	m_LogWriter.push_back(shared_ptr<CLogWriter>(pLogWriter));
}

void CLog::InitWriters()
{
	for (auto writer : m_LogWriter)
	{
		writer->Init();
	}
}