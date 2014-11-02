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

	float a;

	Pixelf(float val)
		: r(val), g(val), b(val), a(1.0f)
	{}

	Pixelf(float rVal, float gVal, float bVal)
		: r(rVal), g(gVal), b(bVal), a(1.0f)
	{}

	Pixelf(float rVal, float gVal, float bVal, float aVal)
		: r(rVal), g(gVal), b(bVal), a(aVal)
	{}

	__inline Pixelf& operator= (float val)
	{
		r = g = b = val;
		return *this;
	}
};