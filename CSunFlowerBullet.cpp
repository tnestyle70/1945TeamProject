#include "pch.h"
#include "CSunFlowerBullet.h"

CSunFlowerBullet::CSunFlowerBullet() 
{
}

CSunFlowerBullet::~CSunFlowerBullet()
{
}

void CSunFlowerBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fSpeed = 10.f; //속도 초기화
}

int CSunFlowerBullet::Update() //Bullet은 상태만 변화, 판단은 MainGame에서 내리기
{
	if (m_bDead)
		return DEAD;

	CObj::Update_Rect();

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY += m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	return NOEVENT;
}

void CSunFlowerBullet::Release()
{
}

void CSunFlowerBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
