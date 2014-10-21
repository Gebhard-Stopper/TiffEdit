#include "stdafx.h"
#include "ScreenLogWriter.h"


CScreenLogWriter::CScreenLogWriter(COutputWnd *pOutputWnd)
	: m_pOutputWnd(pOutputWnd)
{
}


CScreenLogWriter::~CScreenLogWriter()
{
}

void CScreenLogWriter::WriteMessage(shared_ptr<CLogMessage> msg) const
{
	if (m_pOutputWnd)
	{
		m_pOutputWnd->AppendMessage(msg->ToString());
	}
}
