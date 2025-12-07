#pragma once
#include "CObj.h"

class CShield : public CObj
{
public:
	CShield();
	~CShield();
public:
	void Initialize() override;
	int Update() override;
	void Release() override;
	void Render(HDC hDC) override;
public:
	void TryParry(float fAngle);
};