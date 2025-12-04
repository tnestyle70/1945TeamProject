#pragma once
#include "CMonster.h"

class CBossMonster : public CMonster
{
public:
	CBossMonster();
	~CBossMonster();
public:
	void Initialize()override;
	int Update()override;
	void Render(HDC hDC)override;
	void Release()override;
public:
	void CreateSunFlower();
	void CreateSpreadBullet();
	void CreateScrewBullet();
	void CreateBullet();
	void SetBulletDir();
public:
	void SetBossDirection();
	void ResolveCollision();
private:
	float m_fStartAngle;
	float m_fStep;
	float m_fSpread;
	float m_fBulletAngle;
	float m_fBulletCount;
};
