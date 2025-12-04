#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual void Initialize()	PURE;
	virtual int	 Update()	PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()		PURE;
public:
	INFO* GetInfo() { return &m_tInfo; }
	const RECT* GetRect() { return &m_tRect; }
	void	Update_Rect();
	void GetDamage() { m_iLife -= 1; }
	void SetLife(int iLife) { m_iLife = iLife; }
	int GetLife() { return m_iLife; }
	void SetTarget(CObj* pTarget) { m_pTarget = pTarget; }
	CObj* GetTarget() { return m_pTarget; }
	void SetTargetMonster(list<CObj*>* plistMonster) { m_plistMonster = plistMonster; }
	list<CObj*>* GetMonsterListTarget() { return m_plistMonster; }
	bool IsDead() { return m_bDead; }
	void SetAngle(float fAngle) {m_fAngle = fAngle;}
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }
	void SetPos(float fX, float fY) { m_tInfo.fX = fX, m_tInfo.fY = fY; };
	void SetDead() { m_bDead = true; }
	void SetDirection(eDir eDir) { m_eDir = eDir; }
	void SetDirection(float fDirX, float fDirY) {m_fDirX = fDirX, m_fDirY = fDirY;}
protected:
	INFO	m_tInfo;
	RECT	m_tRect;
	eArmor m_eArmor;
	eDir m_eDir;
	DWORD m_dwLastShotTime;
	CObj* m_pTarget;
	list<CObj*>* m_plistMonster;
	int m_iLife;
	bool m_bDead;
	float	m_fSpeed;
	float m_fAngle;
	float m_fDistance;
	float m_fDirX;
	float m_fDirY;
};

