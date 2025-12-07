#pragma once
#include "pch.h"
#include "CBulletAbstract.h"

class CSunFlowerBullet : public CBulletAbstract
{
public:
	CSunFlowerBullet();
	virtual ~CSunFlowerBullet();
public:
	void Initialize() override;
	int Update() override;
	void Release() override;
	void Render(HDC hDC) override;
public:
	void ResolveCollision();
};


