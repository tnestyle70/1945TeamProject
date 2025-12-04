#pragma once
#include "CObj.h"
class CSpreadBullet :
    public CObj
{
public:
	CSpreadBullet();
	virtual ~CSpreadBullet();
public:
	void Initialize() override;
	int Update() override;
	void Release() override;
	void Render(HDC hDC) override;
private:
	float m_fRotateSpeed;
};

