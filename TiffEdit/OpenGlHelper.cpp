#include "stdafx.h"
#include "OpenGlHelper.h"

extern const GLuint MSAA_SAMPLES = 4;

extern unsigned char threeto8[8] =
{
	0, 0111 >> 1, 0222 >> 1, 0333 >> 1, 0444 >> 1, 0555 >> 1, 0666 >> 1, 0377
};

extern unsigned char twoto8[4] =
{
	0, 0x55, 0xaa, 0xff
};

extern unsigned char oneto8[2] =
{
	0, 255
};

extern PIXELFORMATDESCRIPTOR pfd =
{
	sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
	1,                              // version number
	PFD_DRAW_TO_WINDOW |            // support window
	PFD_SUPPORT_OPENGL |        // support OpenGL
	PFD_DOUBLEBUFFER,           // double buffered
	PFD_TYPE_RGBA,                  // RGBA type
	32,                             // 24-bit color depth
	0, 0, 0, 0, 0, 0,               // color bits ignored
	8,                              // 8-bit alpha buffer
	0,                              // shift bit ignored
	0,                              // no accumulation buffer
	0, 0, 0, 0,                     // accum bits ignored
	24,                             // 32-bit z-buffer
	0,                              // no stencil buffer
	0,                              // no auxiliary buffer
	PFD_MAIN_PLANE,                 // main layer
	0,                              // reserved
	0, 0, 0                         // layer masks ignored
};