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
	m_fSpeed = 1.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return DEAD;
	/*
	if (m_eDir == UP)
	{
		m_tInfo.fY -= m_fSpeed;
	}
	if (m_eDir == DOWN)
	{
		m_tInfo.fY += m_fSpeed;
	}
	*/
	m_tInfo.fX += m_fSpeed * m_fDirX;
	m_tInfo.fY += m_fSpeed * m_fDirY;
	
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
