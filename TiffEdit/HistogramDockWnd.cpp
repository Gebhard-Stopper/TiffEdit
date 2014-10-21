// HistogramDockWnd.cpp : implementation file
//

#include "stdafx.h"
#include "TiffEdit.h"
#include "HistogramDockWnd.h"


// CHistogramDockWnd

IMPLEMENT_DYNAMIC(CHistogramDockWnd, CDockablePane)

CHistogramDockWnd::CHistogramDockWnd()
{

}

CHistogramDockWnd::~CHistogramDockWnd()
{
}


BEGIN_MESSAGE_MAP(CHistogramDockWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CHistogramDockWnd message handlers




int CHistogramDockWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndHisto.Create(nullptr, nullptr, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(0, 0, 200, 200), this, WND_HISTOGRAM))
	{
		return -1;
	}

	return 0;
}


void CHistogramDockWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_wndHisto.OnSize(nType, cx, cy);
}
