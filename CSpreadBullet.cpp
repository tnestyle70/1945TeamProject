#include "pch.h"
#include "CSpreadBullet.h"

CSpreadBullet::CSpreadBullet()
{
}

CSpreadBullet::~CSpreadBullet()
{
}

void CSpreadBullet::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 10.f; //속도 초기화
	//m_fRotateSpeed = 5.f;
}

int CSpreadBullet::Update() //Bullet은 상태만 변화, 판단은 MainGame에서 내리기
{
	if (m_bDead)
		return DEAD;
	//m_fAngle += m_fRotateSpeed;
	//구한 세타값을 기준으로 이동
	m_tInfo.fX += m_fSpeed * cosf((m_fAngle) * (PI / 180));
	m_tInfo.fY += m_fSpeed * sinf((m_fAngle) * (PI / 180));

	CObj::Update_Rect();

	ResolveCollision();

	return NOEVENT;
}

void CSpreadBullet::Release()
{
}

void CSpreadBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	for (int i(0); i < m_tInfo.fCX; i++)
	{
		MoveToEx(hDC, m_tRect.left + i, m_tRect.top, nullptr);
		LineTo(hDC, m_tRect.left + i, m_tRect.bottom);
	}
}

void CSpreadBullet::ResolveCollision()
{
	if (m_tRect.right >= WINCX) m_bDead = true; // 오른쪽 경계 닿음/초과
	if (m_tRect.left <= 0)     m_bDead = true; // 왼쪽 경계 닿음/초과
	if (m_tRect.bottom >= WINCY) m_bDead = true; // 아래 경계 닿음/초과
	if (m_tRect.top <= 0)     m_bDead = true; // 위 경계 닿음/초과
}
