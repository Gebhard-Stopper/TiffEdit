#pragma once

#include "RawImage.h"
#include "PixelDef.h"

#define MIN(x,y,z) (x < y)? (x < z)? x : z : (y < z)? y : z
#define MAX(x,y,z) (x > y)? ( x > z)? x : z : (y > z)? y : z

class ColorConverter
{
public:
	__inline static void ConvertToHSV( const Pixelf *pPixelRGB,  Pixelf *pPixelHSV)
	{	
		static float min, max, delta;
		static Pixelf hsvDummy;

		min = MIN(pPixelRGB->r, pPixelRGB->g, pPixelRGB->b);
		max = MAX(pPixelRGB->r, pPixelRGB->g, pPixelRGB->b);

		hsvDummy.v = max;				// v
		delta = max - min;
		
		if (max != 0)
			hsvDummy.s = delta / max;		// s
		else {
			// r = g = b = 0		// s = 0, v is undefined
			hsvDummy.s = 0;
			hsvDummy.h = -1;
			return;
		}

		if (pPixelRGB->r == max)
			hsvDummy.h = (pPixelRGB->g - pPixelRGB->b) / delta;		// between yellow & magenta
		else if (pPixelRGB->g == max)
			hsvDummy.h = 2 + (pPixelRGB->b - pPixelRGB->r) / delta;	// between cyan & yellow
		else
			hsvDummy.h = 4 + (pPixelRGB->r - pPixelRGB->g) / delta;	// between magenta & cyan
		
		hsvDummy.h *= 60;				// degrees
		
		if (hsvDummy.h < 0)
			hsvDummy.h += 360;

		*pPixelHSV = hsvDummy;
	}

	__inline static void ConvertToRGB(const Pixelf *pPixelHSV, Pixelf *pPixelRGB)
	{
		static int i;
		static float f, p, q, t, h;

		if (pPixelHSV->s == 0) {
			// achromatic (grey)
			*pPixelRGB = pPixelHSV->v;
			return;
		}

		h = pPixelHSV->h / 60.0f;
		i = static_cast<int>(h);

		f = h - i;			// factorial part of h
		p = pPixelHSV->v * (1 - pPixelHSV->s);
		q = pPixelHSV->v * (1 - pPixelHSV->s * f);
		t = pPixelHSV->v * (1 - pPixelHSV->s * (1 - f));
		switch (i) 
		{
			case 0:
				pPixelRGB->r = pPixelHSV->v;
				pPixelRGB->g = t;
				pPixelRGB->b = p;
				break;
			case 1:
				pPixelRGB->r = q;
				pPixelRGB->g = pPixelHSV->v;
				pPixelRGB->b = p;
				break;
			case 2:
				pPixelRGB->r = p;
				pPixelRGB->g = pPixelHSV->v;
				pPixelRGB->b = t;
				break;
			case 3:
				pPixelRGB->r = p;
				pPixelRGB->g = q;
				pPixelRGB->b = pPixelHSV->v;
				break;
			case 4:
				pPixelRGB->r = t;
				pPixelRGB->g = p;
				pPixelRGB->b = pPixelHSV->v;
				break;
			default:		// case 5:
				pPixelRGB->r = pPixelHSV->v;
				pPixelRGB->g = p;
				pPixelRGB->b = q;
				break;
		}
	}

	__inline static void ConvertToHSV(CRawImage *pRawImage)
	{		
		_convert(pRawImage, ConvertToHSV);
	}

	__inline static void ConvertToRGB(CRawImage *pRawImage)
	{
		_convert(pRawImage, ConvertToRGB);
	}

	private:
		__inline static void _convert(CRawImage *pRawImage, void(*converter)(const Pixelf*, Pixelf*))
		{
			int nWidth = pRawImage->Width();
			int nHeight = pRawImage->Height();
			auto pBuffer = static_cast<Pixelf*>(const_cast<void*>(pRawImage->GetBitmapBits()));

			for (int y = 0; y < nHeight; ++y)
			{
				for (int x = 0; x < nWidth; ++x)
				{
					auto pPxl = &pBuffer[y*nWidth + x];
					converter(pPxl, pPxl);
				}
			}
		}
};