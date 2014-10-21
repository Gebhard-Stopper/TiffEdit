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

// TiffEditDoc.cpp : implementation of the CTiffEditDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TiffEdit.h"
#endif

#include "TiffEditDoc.h"

#include <propkey.h>
#include "TiffEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTiffEditDoc

IMPLEMENT_DYNCREATE(CTiffEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CTiffEditDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTiffEditDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_ITiffEdit to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {64E90099-2D8C-40A6-A0EF-E6B81E50C91B}
static const IID IID_ITiffEdit =
{ 0x64E90099, 0x2D8C, 0x40A6, { 0xA0, 0xEF, 0xE6, 0xB8, 0x1E, 0x50, 0xC9, 0x1B } };

BEGIN_INTERFACE_MAP(CTiffEditDoc, CDocument)
	INTERFACE_PART(CTiffEditDoc, IID_ITiffEdit, Dispatch)
END_INTERFACE_MAP()


// CTiffEditDoc construction/destruction

CTiffEditDoc::CTiffEditDoc()
	:m_pTiffImage(nullptr)
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CTiffEditDoc::~CTiffEditDoc()
{
	if (m_pTiffImage) {
		delete m_pTiffImage;
	}

	AfxOleUnlockApp();
}

BOOL CTiffEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CTiffEditDoc serialization

void CTiffEditDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CTiffEditDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CTiffEditDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CTiffEditDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTiffEditDoc diagnostics

#ifdef _DEBUG
void CTiffEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTiffEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTiffEditDoc commands


BOOL CTiffEditDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	m_pTiffImage = CTiffImage::Open(lpszPathName);

	BOOL bResult =  m_pTiffImage != nullptr;

	POSITION pos = GetFirstViewPosition();
	CTiffEditView *pView = static_cast<CTiffEditView*>(GetNextView(pos));

	if (pView) {
		pView->OnDocumentLoaded();
	}

	return bResult;
}

void* CTiffEditDoc::GetImageBuffer()
{
	if (m_pTiffImage)
	{
		return m_pTiffImage->GetBitmapBits();
	}

	return nullptr;
}

CImageBase* CTiffEditDoc::GetImage() const
{
	return m_pTiffImage;
}

void CTiffEditDoc::NextImage()
{
	if (m_pTiffImage)
	{
		static_cast<CTiffImage*>(m_pTiffImage)->NextDirectory();
	}
}

void CTiffEditDoc::PreviousImage()
{
	if (m_pTiffImage)
	{
		static_cast<CTiffImage*>(m_pTiffImage)->PreviousDirectory();
	}
}