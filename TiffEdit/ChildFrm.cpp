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

// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "TiffEdit.h"

#include "ChildFrm.h"
#include "TiffEditView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CChildFrame::OnUpdateFilePrintPreview)
	ON_WM_MDIACTIVATE()
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	EnableActiveAccessibility();
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame message handlers

void CChildFrame::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CChildFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // force Print Preview mode closed
	}
}

void CChildFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}


void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	CTiffEditView* pView = static_cast<CTiffEditView*>(GetActiveView());

	if (pView)
	{
		if (bActivate)
		{
			pView->EnableDrawing();
			auto pDoc = pView->GetDocument();

			if (pDoc)
			{
				auto pImg = pDoc->GetImage();
				FillPropertyWindow(pImg);
			}
		}
		else
		{
			pView->DisableDrawing();
		}
	}
}

void CChildFrame::FillPropertyWindow(CImageBase *pImg)
{
	if (!pImg) return;

	CMainFrame *pMainFrm = static_cast<CMainFrame*>(GetParentFrame());

	if (pMainFrm)
	{
		auto pPropWnd = pMainFrm->GetPropertyWindow();

		if (pPropWnd)
		{
			pPropWnd->Clear();

			auto pGroup = pPropWnd->AddPropertyGroup(_T("Image"));
			pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Name"), _T("")));
			pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Directory"), _T("")));
			pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Width"), (_variant_t)pImg->Width(), _T("The image width in pixel")));
			pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Height"), (_variant_t)pImg->Height(), _T("The image height in pixel")));
			pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Bits per pixel"), (_variant_t)pImg->BitsPerPixel(),  _T("The number of bits for each pixel in the image")));
			pGroup->AllowEdit(FALSE);
			pGroup->Expand();

			AddExtendedImageProperties(pPropWnd, pImg);
		}
	}
}

void CChildFrame::AddExtendedImageProperties(CPropertiesWnd *pPropWnd, CImageBase *pImg)
{
	switch (pImg->GetImageContainerFormat())
	{
	case CImageBase::Tiff:
		AppendTiffImageProperties(pPropWnd, pImg);
		break;
	default:
		break;
	}
}

void CChildFrame::AppendTiffImageProperties(CPropertiesWnd *pPropWnd, CImageBase *pImg)
{
	CTiffImage *pImage = static_cast<CTiffImage*>(pImg);

	auto pImageIageInfoEx = static_cast<CTiffImageInfo*>(pImg->GetImageInfo()->GetExtendedImageInfo());

	auto pGroup = pPropWnd->AddPropertyGroup(_T("Extended Info"));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Directories"), pImageIageInfoEx->m_nDirectoryCount, _T("The number of layers (sub-images)")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Compression"), pImageIageInfoEx->m_nCompression, _T("The applied image-compression scheme"))); //ToDo: Get String with compresseion name
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("X-Resolution"), pImageIageInfoEx->m_nXResolution, _T("The number of pixels per ResolutionUnit in the ImageWidth direction")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Y-Resolution"), pImageIageInfoEx->m_nYResolution, _T("The number of pixels per ResolutionUnit in the ImageHeight direction")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Resolutionunit"), pImageIageInfoEx->m_nResolutionUnit, _T("The unit of measurement for XResolution and YResolution."))); //ToDo: Get string with unit name
	pGroup->AllowEdit(FALSE);
	pGroup->Expand();

	pGroup = pPropWnd->AddPropertyGroup(_T("Info"));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Software"), pImageIageInfoEx->m_strSoftware, _T("Name and version number of the software package(s) used to create the image")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Timestamp"), pImageIageInfoEx->m_dtCreated.Format(), _T("Date and time of image creation")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Artist"), pImageIageInfoEx->m_strArtist, _T("Person who created the image. Note: some older TIFF files used this tag for storing Copyright information")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Host Computer"), pImageIageInfoEx->m_strHostName, _T("he computer and/or operating system in use at the time of image creation")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Copyright"), pImageIageInfoEx->m_strCopyright, _T("Copyright notice of the person or organization that claims the copyright to the image")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("Description"), pImageIageInfoEx->m_strDescription, _T("A string that describes the subject of the image")));
	pGroup->AllowEdit(FALSE);
	pGroup->Expand();
}