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
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 10.f; //속도 초기화
	m_eBulletInfo = eBulletInfo::NORMAL_BULLET;
}

int CSunFlowerBullet::Update() //Bullet은 상태만 변화, 판단은 MainGame에서 내리기
{
	if (m_bDead)
		return DEAD;

	CObj::Update_Rect();

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY += m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	ResolveCollision();

	return NOEVENT;
}

void CSunFlowerBullet::Release()
{
}

void CSunFlowerBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	for (int i(0); i < m_tInfo.fCX; i++)
	{
		MoveToEx(hDC, m_tRect.left + i, m_tRect.top, nullptr);
		LineTo(hDC, m_tRect.left + i, m_tRect.bottom);
	}
}

void CSunFlowerBullet::ResolveCollision()
{
	if (m_tRect.right >= WINCX) m_bDead = true; // 오른쪽 경계 닿음/초과
	if (m_tRect.left <= 0)     m_bDead = true; // 왼쪽 경계 닿음/초과
	if (m_tRect.bottom >= WINCY) m_bDead = true; // 아래 경계 닿음/초과
	if (m_tRect.top <= 0)     m_bDead = true; // 위 경계 닿음/초과
}
