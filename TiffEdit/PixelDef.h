#pragma once

#define _PIXELRGB
#define _PIXELHSV

enum ColorChannel {Hue = 0x0, Saturation = 0x1, Value = 0x2, Alpha = 0x3};

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

	__inline Pixelf() 
		: a(1.0f)
		{}

	__inline Pixelf(float val)
		: r(val), g(val), b(val), a(1.0f)
		{}

	__inline Pixelf(float rVal, float gVal, float bVal)
		: r(rVal), g(gVal), b(bVal), a(1.0f)
		{}

	__inline Pixelf(float rVal, float gVal, float bVal, float aVal)
		: r(rVal), g(gVal), b(bVal), a(aVal)
		{}

	__inline Pixelf& operator = (float val)
	{
		r = g = b = val;
		return *this;
	}

	__inline Pixelf& operator -= (const Pixelf& val)
	{
		h -= val.h;
		s -= val.s;
		v -= val.v;

		return *this;
	}

	__inline Pixelf& operator += (const Pixelf& val)
	{
		h += val.h;
		s += val.s;
		v += val.s;

		return *this;
	}

	__inline Pixelf operator - (const Pixelf& val) const
	{
		return Pixelf(h - val.h, s - val.s, v - val.v);
	}

	__inline Pixelf operator - (float val) const
	{
		return Pixelf(h - val, s - val, v - val);
	}

	__inline Pixelf operator * (float val) const
	{
		return Pixelf(h * val, s * val, v * val);
	}

	__inline float& operator[] (ColorChannel nChannel)
	{
		return reinterpret_cast<float*>(this)[nChannel];
	}
};

#ifndef OPERATOR_MINUS
#define OPERATOR_MINUS

__inline Pixelf operator -(float fVal, const Pixelf& pVal)
{
	return Pixelf(fVal - pVal.h, fVal - pVal.s, fVal - pVal.v);
}

#endif