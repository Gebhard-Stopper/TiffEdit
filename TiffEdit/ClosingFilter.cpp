#include "stdafx.h"
#include "ClosingFilter.h"
#include "ErosionFilter.h"
#include "DilationFilter.h"


CClosingFilter::CClosingFilter()
	: CFilterGroup(_T("Closing Filter"))
{
	AddFilter(new CDilationFilter);
	AddFilter(new CErosionFilter);
}


CClosingFilter::~CClosingFilter()
{
}
