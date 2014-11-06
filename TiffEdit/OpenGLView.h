#pragma once
#include "RectF.h"
#include "PointF.h"
#include "ShaderMngr.h"


class COpenGLView 
	: public CView
{
	DECLARE_DYNCREATE(COpenGLView)

protected:
	CRectF		 m_rcDomain;				/**< RectF, specifying the entire domain of the currently opened data set.*/
	CRectF		 m_rcViewPort;				/**< RectF, specifying the current viewport. Can be smaller or equal than m_rcDomain. */
	CPointF		 m_ptViewportCenter;		/**< CPointf, specifying the center of the view port. Used to zoom near the current mouse location.*/
	int			 m_xExtent;					/**< Extent of the canvas in pixels in X-direction */
	int			 m_yExtent;					/**< Extent of the canvas in pixels in Y-direction */
	int			 m_xMin;					/**< Offset in pixels in X-direction. Used to center the displayed image horizontally. */
	int			 m_yMin;					/**< Offset in pixels in Y-direction. Used to center the displayed image vertically. */

	float		 m_xyRatio;					/**< Width/height ratio of the extents (m_xExtent/m_yExtent). */
	float		 m_fPixelUnitRatioX;		/**< Pixels per domain unit in X-direction. */
	float		 m_fPixelUnitRatioY;		/**< Pixels per domain unit in Y-direction. */

	float		 m_fIsoVal;					/**< Current iso-value to render iso contours. */
	BOOL		 m_bDrawCoordinateAxes;		/**< Flag, that determines if coordinate axes are drawn around the domain. */

	int			 m_nColorOffset;			/**< Manipulator for the base color for drawing the vector field. */

	int			 m_nMSAASamples;			/**< Number of samples used for multisampling.*/

	static BOOL m_bGlewInitialized;

	CShaderMngr	m_ShdrMngr;

//needed for WGL
protected:
	CPalette	 m_cPalette;				/**< Color palette, needed by m_pDC.*/
	CPalette	*m_pOldPalette;				/**< Buffer for m_cPalette.*/
	CRect		 m_oldRect;					/**< Screen rectangle.*/
	CClientDC	*m_pDC;						/**< Windows device context to create the OpenGl context.*/
	HGLRC		 m_hRc;						/**< Handle to the OpenGL render context. */
	int			 m_nPixelFormatMSAA;			/**< Index that identifies the pixel format to set. The various pixel formats supported by a device context are identified by one-based indexes. */

public:
	COpenGLView();
	virtual ~COpenGLView();

protected:
	/**
	*	Initializes OpenGL (WGL), GLUT and GLEW.bSetupPixelFormat()
	*/
	void Init();

	/**
	*	Setup the pixel format of this CFlowIllustratorRenderView's device context.
	*	This function tries to setup a pixel format that supports MSAA, in order to
	*	achieve a smooth output image.
	*
	*	@return TRUE, if successful, otherwise false.
	*
	*	@remarks	If this function fails, the pixel format could not be set correctly.
	*				This might lead display errors.
	*/
	BOOL bSetupPixelFormat();

	/**
	*	Helper function, called by bSetupPixelFormat().
	*
	*	@remarks	If this function fails, the pixel format could not be set correctly.
	*				This might lead display errors.
	*/
	BOOL bSetupDummyPixelFormat(HDC hDC);

	/**
	*	Set the orthographic projection to the specified screen region.
	*
	*	@param left		The coordinates for the left vertical clipping plane.
	*	@param right	The coordinates for the right vertical clipping plane.
	*	@param bottom	The coordinates for the bottom horizontal clipping plane.
	*	@param top		The coordinates for the top horizontal clipping plans.
	*	@param zNear	The distances to the nearer depth clipping plane. This distance is negative if the plane is to be behind the viewer.
	*	@param zFar		The distances to the farther depth clipping plane. This distance is negative if the plane is to be behind the viewer.
	*/
	void SetProjection(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear = 0.0, GLdouble zFar = -1.0);

	/**
	*	Adjust the viewport, according to the current zoom factor.
	*
	*	@param bCenterOnMousePos If TRUE, the current mouse location is used as the new viewport center.
	*
	*/
	void AdjustViewport(BOOL bCenterOnMousePos = FALSE);

	/**
	*	Calculates the extent of the viewport in X and Y direction, with regard to
	*	the current zoom factor.
	*/
	void CalcExtents(void);

	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* /*pDC*/);
};

