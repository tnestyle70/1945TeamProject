#pragma once
#include "CMonster.h"

class CNormalMonster : public CMonster
{
public:
	CNormalMonster();
	virtual ~CNormalMonster();
public:
	void Initialize()override;
	int Update()override;
	void Render(HDC hDC)override;
	void Release()override;
public:
	void CreateBullet();
	void SetBulletDir(float fX, float fY, float fAngle);
};