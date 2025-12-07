#pragma once
#include "pch.h"
#include "CBulletAbstract.h"

class CScrewBullet : public CBulletAbstract
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();
public:
	void Initialize() override;
	int Update() override;
	void Release() override;
	void Render(HDC hDC) override;
public:
	void SetPlayer() {}
	void ResolveCollision();
private:
	POINT m_tCenter; //기준으로 돌아갈 중심
	float m_fRotateAngle;
	float m_fRotateSpeed;
	bool m_bStart;
};
