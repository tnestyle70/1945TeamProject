#pragma once
#include "CObj.h"

class CMonster : public CObj
{
public:
	CMonster();
	~CMonster();
public:
	void Initialize()override;
	int Update()override;
	void Render(HDC hDC)override;
	void Release()override;
public:
	void SetBullet(list<CObj*>* m_pMonsterBulletList)
	{
		m_pBulletList = m_pMonsterBulletList;
	}
	void CreateBullet();
	void SetBulletDir(float fX, float fY, float fAngle);
private:
	list<CObj*>* m_pBulletList;
	bool m_bOnLimitLine;
};
