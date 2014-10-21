#include "stdafx.h"
#include "RectF.h"


CRectF::CRectF()
{
}


CRectF::~CRectF()
{
}

float CRectF::GetWidth() const
{
	return  m_Max.x - m_Min.x;
}

float CRectF::GetHeight() const
{
	return m_Max.y - m_Min.y;
}