#pragma once
#include "LogWriter.h"
#include "OutputWnd.h"

class CScreenLogWriter :
	public CLogWriter
{
private:
	COutputWnd	*m_pOutputWnd;

public:
	CScreenLogWriter(COutputWnd *pOutputWnd);
	virtual ~CScreenLogWriter();

public:
	virtual void WriteMessage(shared_ptr<CLogMessage> msg) const;
};

