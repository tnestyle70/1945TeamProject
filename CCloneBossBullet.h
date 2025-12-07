#pragma once
#include "CBulletAbstract.h"

class CCloneBossBullet :
    public CBulletAbstract
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
	float& GetOriginAngle() { return m_fOriginAngle; }
private:
	float m_fOriginAngle;
	bool m_bStart;
};

