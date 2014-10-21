#pragma once
#include "PointF.h"

class CRectF
{
public:
	CPointF	m_Min;
	CPointF m_Max;

public:
	CRectF();
	~CRectF();

public:
	float GetWidth() const;
	float GetHeight() const;
};

