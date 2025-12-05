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

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180));
	
	__super::Update_Rect();
	
	if (m_tRect.bottom >= WINCY || m_tRect.top <= 0)
		return DEAD;

	__super::Update_Rect();
	
	return NOEVENT;
}

void CBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}
