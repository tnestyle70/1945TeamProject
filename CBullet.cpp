#include "pch.h"
#include "CBullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 10.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return DEAD;
	//발사시 고정된 앵글을 가진 상태에서 발사되는 총알
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180));
	
	__super::Update_Rect();
	
	if (m_tRect.bottom >= WINCY || m_tRect.top <= 0)
		return DEAD;

	__super::Update_Rect();

	ResolveCollision();
	
	return NOEVENT;
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	for (int i(0); i < m_tInfo.fCX; i++)
	{
		MoveToEx(hDC, m_tRect.left + i, m_tRect.top, nullptr);
		LineTo(hDC, m_tRect.left + i, m_tRect.bottom);
	}
}

void CBullet::Release()
{
}

void CBullet::ResolveCollision()
{
	if (m_tRect.right >= WINCX) m_bDead = true; // 오른쪽 경계 닿음/초과
	if (m_tRect.left <= 0)     m_bDead = true; // 왼쪽 경계 닿음/초과
	if (m_tRect.bottom >= WINCY) m_bDead = true; // 아래 경계 닿음/초과
	if (m_tRect.top <= 0)     m_bDead = true; // 위 경계 닿음/초과
}
