#include "stdafx.h"
#include "OpeningFilter.h"
#include "ErosionFilter.h"
#include "DilationFilter.h"

COpeningFilter::COpeningFilter()
	: CFilterGroup(_T("Opening Filter"))
{
	AddFilter(new CErosionFilter);
	AddFilter(new CDilationFilter);
}


COpeningFilter::~COpeningFilter()
{
}