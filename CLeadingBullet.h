#pragma once
#include "pch.h"
#include "CObj.h"

class CLeadingBullet : public CObj
{
public:
	CLeadingBullet();
	virtual ~CLeadingBullet();
public:
	void Initialize() override;
	int Update() override;
	void Release() override;
	void Render(HDC hDC) override;
public:
	CObj* FindNearestMonster();
private:
	CObj* m_pNearMonster;
};
