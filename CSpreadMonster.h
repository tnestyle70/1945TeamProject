#pragma once
#include "CMonster.h"

class CSpreadMonster : public CMonster
{
public:
	CSpreadMonster();
	~CSpreadMonster();
public:
	void Initialize()override;
	int Update()override;
	void Render(HDC hDC)override;
	void Release()override;
public:
	void CreateSunFlower();
	void CreateSpiralBullet();
	void CreateBullet();
	void SetBulletDir(float fX, float fY, float fAngle);
private:
	float m_fSunFlowerAngle;
};

