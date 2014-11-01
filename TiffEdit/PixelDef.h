#pragma once

#define _PIXELRGB
#define _PIXELHSV

struct Pixelf
{
	union
	{
		struct
		{
			float r, g, b;
		} _PIXELRGB;

		struct
		{
			float h, s, v;
		} _PIXELHSV;
	};

	__inline Pixelf& operator= (float val)
	{
		r = g = b = val;
	}
};