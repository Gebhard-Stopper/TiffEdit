#include "stdafx.h"
#include "PointF.h"


CPointF::CPointF()
	:CPointF(0,0)
{
}

CPointF::CPointF(float xPos, float yPos)
	: x(xPos), y(yPos)
{}


CPointF::~CPointF()
{
}
