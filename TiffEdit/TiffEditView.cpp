// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// TiffEditView.cpp : implementation of the CTiffEditView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TiffEdit.h"
#endif

#include "TiffEditDoc.h"
#include "TiffEditView.h"
#include "Log.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTiffEditView

IMPLEMENT_DYNCREATE(CTiffEditView, CView)

BEGIN_MESSAGE_MAP(CTiffEditView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTiffEditView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CTiffEditView construction/destruction

CTiffEditView::CTiffEditView()
{
	EnableActiveAccessibility();
	m_bDrawingEnabled = TRUE;
	// TODO: add construction code here

}

CTiffEditView::~CTiffEditView()
{
}

BOOL CTiffEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COpenGLView::PreCreateWindow(cs);
}

// CTiffEditView drawing

void CTiffEditView::OnDraw(CDC* /*pDC*/)
{
	

	//if (!m_bDrawingEnabled) return;

	auto pParentFrame = GetParentFrame();
	if (pParentFrame) {
		if (pParentFrame->GetActiveView() != this)
			return;
	}

	DrawScene();

	
}

void CTiffEditView::DrawScene()
{
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRc);

	CTiffEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2);

	auto pPixelBuffer = pDoc->GetImage();
	pPixelBuffer->Draw();

	glFinish();

	SwapBuffers(wglGetCurrentDC());

	wglMakeCurrent(NULL, NULL);
}


// CTiffEditView printing
void CTiffEditView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTiffEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTiffEditView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTiffEditView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTiffEditView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTiffEditView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTiffEditView diagnostics

#ifdef _DEBUG
void CTiffEditView::AssertValid() const
{
	CView::AssertValid();
}

void CTiffEditView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTiffEditDoc* CTiffEditView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTiffEditDoc)));
	return (CTiffEditDoc*)m_pDocument;
}
#endif //_DEBUG


// CTiffEditView message handlers


int CTiffEditView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COpenGLView::OnCreate(lpCreateStruct) == -1)
		return -1;

	OnDocumentLoaded();

	return 0;
}

void CTiffEditView::OnDocumentLoaded()
{
	auto pDoc = GetDocument();
	if (pDoc)
	{
		auto pImage = pDoc->GetImage();
		if (pImage){
			m_xExtent = pImage->Width();
			m_yExtent = pImage->Height();
			m_rcViewPort.m_Max.x = m_xExtent;
			m_rcViewPort.m_Max.y = m_yExtent;
		}

		EnableDrawing();

		AdjustViewport();
		CalcExtents();
	}
}


void CTiffEditView::EnableDrawing()
{
	m_bDrawingEnabled = TRUE;

	AdjustViewport();
	CalcExtents();
}

void CTiffEditView::DisableDrawing()
{
	m_bDrawingEnabled = FALSE;
}

void CTiffEditView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	if (bActivate) {
		EnableDrawing();
	}else{
		DisableDrawing();
	}
	
	COpenGLView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


BOOL CTiffEditView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (nFlags & MK_SHIFT)
	{
		auto pDoc = GetDocument();

		if (zDelta < 0)
		{
			pDoc->NextImage();
		}
		else
		{
			pDoc->PreviousImage();
		}

		DrawScene();
	}

	return COpenGLView::OnMouseWheel(nFlags, zDelta, pt);
}

void CTiffEditView::ApplyFilter(CFilterBase& filter, ColorChannel nColorChannel)
{
	auto pDoc = GetDocument();

	if (pDoc)
	{
		auto pImage = pDoc->GetImage();
		if (pImage)
		{
			pImage->ApplyFilter(filter, nColorChannel);
			RedrawWindow();
		}
	}
}