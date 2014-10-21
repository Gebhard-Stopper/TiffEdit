#pragma once
#include <list>
#include <memory>
#include "LogMessage.h"

using namespace std;

// CLogWriter

class CLogWriter : public CWinThread
{
	DECLARE_DYNCREATE(CLogWriter)

private:
	list<shared_ptr<CLogMessage>>	m_Queue;
	CMutex	m_MutexQueue;
	CEvent	m_QueueNotEmpty;
	BOOL	m_bInitialized;

protected:
	CLogWriter();           // protected constructor used by dynamic creation

public:
	virtual ~CLogWriter();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	virtual int Run();

	virtual void WriteMessage(shared_ptr<CLogMessage> msg) const {};

private:
	shared_ptr<CLogMessage> _popMessage();
	void _chefkIfQueueEmpty();

public:
	void Enqueue(shared_ptr<CLogMessage> msg);
	virtual BOOL Init();
	void Stop() { m_bInitialized = FALSE; }

protected:
	DECLARE_MESSAGE_MAP()
};


