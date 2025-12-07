#pragma once
#include "pch.h"
#include "CObj.h"

class CSunFlowerBullet : public CObj
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


