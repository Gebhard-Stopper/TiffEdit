#pragma once
#include "HistogramWnd.h"

// CHistogramDockWnd

class CHistogramDockWnd : public CDockablePane
{
	DECLARE_DYNAMIC(CHistogramDockWnd)

protected:
	CHistogramWnd	m_wndHisto;

public:
	CHistogramDockWnd();
	virtual ~CHistogramDockWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


