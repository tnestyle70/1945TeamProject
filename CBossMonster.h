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
	void DropItem()override;
	void CreateSunFlower();
	void CreateSpreadBullet(int iCount, float fOffset);
	void CreateScrewBullet();
	void CreateBullet();
	void CreateOrbitClone();
	void CreateLineClone();
	void CreateRandomClone();
	void SetBulletDir();
public:
	void SetBossDirection();
	void ResolveCollision();
	void FaceRender(HDC hDC);
private:
	eArmor m_eArmor;
	float m_fStartAngle;
	float m_fStep;
	float m_fSpread;
	float m_fBulletAngle;
	float m_fBulletCount;
	DWORD m_dLastSpawnTime;
};
