#include "stdafx.h"
#include "FilterGroup.h"


CFilterGroup::CFilterGroup(const CString& strFiltername)
	: CFilterBase(strFiltername)
{
}


CFilterGroup::~CFilterGroup()
{
}

int CFilterGroup::AddFilter(CFilterBase *pNewFilter)
{
	m_Filter.push_back(shared_ptr<CFilterBase>(pNewFilter));
	return m_Filter.size() - 1;
}

void CFilterGroup::RemoveFilter(int nIndex)
{
	if (nIndex >= 0 && nIndex < m_Filter.size())
	{
		m_Filter.erase(m_Filter.begin() + nIndex);
	}
}

CFilterBase* CFilterGroup::GetFilter(int nIndex) const
{
	if (nIndex >= 0 && nIndex < m_Filter.size())
	{
		return m_Filter[nIndex].get();
	}

	return nullptr;
}

void CFilterGroup::_onApplyFilter(CRawImage *pImage, ColorChannel nColorChannel)
{
	for (auto filter : m_Filter) {
		filter->ApplyFilter(pImage, nColorChannel);
	}
}