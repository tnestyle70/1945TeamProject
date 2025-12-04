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
	void SetBullet(list<CObj*>* m_pMonsterBulletList) {m_pBulletList = m_pMonsterBulletList;}
	void SetLimitLine(float fLimitLine) { m_fLimitLine = fLimitLine; }
protected:
	list<CObj*>* m_pBulletList;
	bool m_bOnLimitLine;
	float m_fLimitLine;
};
