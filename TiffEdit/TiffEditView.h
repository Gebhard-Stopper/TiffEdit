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

// TiffEditView.h : interface of the CTiffEditView class
//

#pragma once
#include "OpenGLView.h"
#include "TiffEditDoc.h"
#include "FilterBase.h"

class CTiffEditView : public COpenGLView
{
protected:
	BOOL	m_bDrawingEnabled;

protected: // create from serialization only
	CTiffEditView();
	DECLARE_DYNCREATE(CTiffEditView)

// Attributes
public:
	CTiffEditDoc* GetDocument() const;

// Operations

	void EnableDrawing();
	void DisableDrawing();

protected:
	void DrawScene();

public:
	void ApplyFilter(CFilterBase& filter, ColorChannel nColorChannel = ColorChannel::Value);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTiffEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void OnDocumentLoaded();


protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in TiffEditView.cpp
inline CTiffEditDoc* CTiffEditView::GetDocument() const
   { return reinterpret_cast<CTiffEditDoc*>(m_pDocument); }
#endif

