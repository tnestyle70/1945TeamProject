#pragma once
#include "CBulletAbstract.h"
class CSpreadBullet :
    public CBulletAbstract
{
public:
	CSpreadBullet();
	virtual ~CSpreadBullet();
public:
	void Initialize() override;
	int Update() override;
	void Release() override;
	void Render(HDC hDC) override;
public:
	void ResolveCollision();
private:
	float m_fRotateSpeed;
};

