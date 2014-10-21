// LogWriter.cpp : implementation file
//

#include "stdafx.h"
#include "TiffEdit.h"
#include "LogWriter.h"


// CLogWriter

IMPLEMENT_DYNCREATE(CLogWriter, CWinThread)

CLogWriter::CLogWriter()
: m_MutexQueue(FALSE), m_QueueNotEmpty(FALSE, TRUE)
{
}

CLogWriter::~CLogWriter()
{
	Stop();
}

BOOL CLogWriter::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CLogWriter::ExitInstance()
{
	//Flush the remainig queue items

	for (auto logMessage : m_Queue)
	{
		WriteMessage(logMessage);
	}


	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CLogWriter, CWinThread)
END_MESSAGE_MAP()


// CLogWriter message handlers
void CLogWriter::Enqueue(shared_ptr<CLogMessage> msg)
{
	CSingleLock(&m_MutexQueue, TRUE);
	m_Queue.push_back(msg);
	m_QueueNotEmpty.SetEvent();
}

int CLogWriter::Run()
{
	while (m_bInitialized)
	{
		_chefkIfQueueEmpty();

		::WaitForSingleObject(m_QueueNotEmpty, INFINITE);

		auto currMsg = _popMessage();

		WriteMessage(currMsg);
	}

	ExitInstance();

	return 0;
}

shared_ptr<CLogMessage> CLogWriter::_popMessage()
{
	CSingleLock(&m_MutexQueue, TRUE);
	shared_ptr<CLogMessage> retVal = m_Queue.front();
	m_Queue.pop_front();

	 return retVal;
}

void CLogWriter::_chefkIfQueueEmpty()
{
	CSingleLock(&m_MutexQueue, TRUE);
	if (m_Queue.size() == 0)
	{
		m_QueueNotEmpty.ResetEvent();
	}
}

BOOL CLogWriter::Init()
{
	m_bInitialized =  CreateThread();
	return m_bInitialized;
}