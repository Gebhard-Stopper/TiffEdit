// OpenGLWnd.cpp : implementation file
//

#include "stdafx.h"
#include "TiffEdit.h"
#include "OpenGLWnd.h"
#include "OpenGlDummyWnd.h"
#include "OpenGlHelper.h"

// COpenGLWnd

IMPLEMENT_DYNAMIC(COpenGLWnd, CWnd)

COpenGLWnd::COpenGLWnd()
{
	m_pDC = nullptr;
	m_pOldPalette = nullptr;
	m_fPixelUnitRatioX = 1.0f;
	m_fPixelUnitRatioY = 1.0f;
	m_fIsoVal = 0.0f;
	m_nColorOffset = 0;
	m_xExtent = 512;
	m_yExtent = 512;
	m_xMin = 0;
	m_yMin = 0;
	m_rcDomain.m_Min.x = 0;
	m_rcDomain.m_Min.y = 0;
	m_rcDomain.m_Max.x = 1;
	m_rcDomain.m_Max.y = 1;

	m_rcViewPort = m_rcDomain;

	m_bDrawCoordinateAxes = TRUE;
	m_ptViewportCenter = CPointF(0.5f, 0.5f);
}

COpenGLWnd::~COpenGLWnd()
{
}


BEGIN_MESSAGE_MAP(COpenGLWnd, CWnd)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// COpenGLWnd message handlers

void COpenGLWnd::Init()
{
	if (!m_pDC)
		m_pDC = new CClientDC(this);

	ASSERT(m_pDC != NULL);

	if (bSetupPixelFormat())
		glEnable(GL_MULTISAMPLE_ARB);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	GetClientRect(&m_oldRect);
	glDisable(GL_DEPTH_TEST);

	SetProjection(0, m_oldRect.Width(), 0, m_oldRect.Height());
}

void COpenGLWnd::SetProjection(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0f, fAspect, fNearPlane, fFarPlane);
	glOrtho(left, right, bottom, top, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
}

void COpenGLWnd::AdjustViewport(BOOL bCenterOnMousePos)
{
	glViewport(m_xMin, m_yMin, m_xExtent, m_yExtent);
	SetProjection(m_rcViewPort.m_Min.x, m_rcViewPort.m_Max.x, m_rcViewPort.m_Max.y, m_rcViewPort.m_Min.y);
}

void COpenGLWnd::CalcExtents()
{
}

BOOL COpenGLWnd::bSetupPixelFormat()
{
	COpenGlDummyWnd dummy;

	BOOL bResult = dummy.Create(_T("STATIC"), NULL, WS_CHILD, CRect(0, 0, 50, 50), this, 1234);

	GLint maxSamples;

	//get the maximum supported number of MSAA samples
	glGetIntegerv(GL_MAX_SAMPLES_EXT, &maxSamples);
	if (maxSamples > 16) maxSamples = 16;

	int attributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 8,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB, 1,
		WGL_SAMPLES_ARB, maxSamples,
		0, 0
	};

	UINT numFormats = 0;
	BOOL bStatus = FALSE;

	bStatus = wglChoosePixelFormatARB(dummy.GetSafeHDC(), attributes, 0, 1,
		&m_nPixelFormatMSAA, &numFormats);

	if (!bStatus == TRUE || !numFormats)
	{
		m_nPixelFormatMSAA = dummy.m_nPixelFormat;
	}

	return bSetupDummyPixelFormat(m_pDC->GetSafeHdc());
}

BOOL COpenGLWnd::bSetupDummyPixelFormat(HDC hDC)
{
	if (SetPixelFormat(hDC, m_nPixelFormatMSAA, &pfd) == FALSE)
		return FALSE;

	m_hRc = wglCreateContext(hDC);
	if (!m_hRc)
		return FALSE;

	if (!wglMakeCurrent(hDC, m_hRc))
		return FALSE;

	return TRUE;
}

void COpenGLWnd::OnDestroy()
{
	CWnd::OnDestroy();

	::wglMakeCurrent(NULL, NULL);

	if (m_hRc)
		::wglDeleteContext(m_hRc);

	if (m_pOldPalette)
		m_pDC->SelectPalette(m_pOldPalette, FALSE);

	if (m_pDC)
		m_pDC->DeleteDC();
}


BOOL COpenGLWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


int COpenGLWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	Init();

	return 0;
}


void COpenGLWnd::OnPaint()
{
	CPaintDC dc(this); 

	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRc);

	glClear(GL_COLOR_BUFFER_BIT);

	OnDraw(&dc);

	glFinish();

	SwapBuffers(wglGetCurrentDC());

	wglMakeCurrent(NULL, NULL);
}


void COpenGLWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (cy > 0)
	{
		m_oldRect.right = cx;
		m_oldRect.bottom = cy;

		AdjustViewport();
		CalcExtents();

		Invalidate();
	}
}


BOOL COpenGLWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CWnd::PreCreateWindow(cs);
}
