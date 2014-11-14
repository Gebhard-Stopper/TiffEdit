#pragma once
#include "FilterBase.h"
#include <vector>
#include <memory>

using namespace std;

class CFilterGroup :
	public CFilterBase
{
private:
	vector<shared_ptr<CFilterBase>> m_Filter;

public:
	CFilterGroup(const CString& strFiltername);
	~CFilterGroup();

public:
	int AddFilter(CFilterBase *pNewFilter);
	void RemoveFilter(int nIndex);

	CFilterBase* GetFilter(int nIndex) const;

private://not applicable here
	virtual void _onApplyFilter(CRawImage *pImage, const CFilterParam* pParams);
};

