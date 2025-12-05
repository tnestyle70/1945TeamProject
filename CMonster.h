#pragma once
#include "CObj.h"

class CMonster : public CObj
{
public:
	CMonster() {};
	virtual ~CMonster() {};
public:
	virtual void Initialize()PURE;
	virtual int Update()PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()PURE;
public:
	virtual void DropItem()PURE;
	void SetLimitLine(float fLimitLine) { m_fLimitLine = fLimitLine; }
protected:
	bool m_bOnLimitLine;
	bool m_bDropItem;
	float m_fLimitLine;
};
