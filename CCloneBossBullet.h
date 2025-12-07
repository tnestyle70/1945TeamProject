#pragma once
#include "CObj.h"

class CCloneBossBullet :
    public CObj
{
public:
	CCloneBossBullet();
	~CCloneBossBullet();
public:
	void Initialize() override;
	int Update() override;
	void Release() override;
	void Render(HDC hDC) override;
public:
	void ResolveCollision();
private:
	bool m_bStart;
};

