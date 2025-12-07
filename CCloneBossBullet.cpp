#include "pch.h"
#include "CCloneBossBullet.h"
#include "CObjMgr.h"

CCloneBossBullet::CCloneBossBullet()
{
}

CCloneBossBullet::~CCloneBossBullet()
{
}

void CCloneBossBullet::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 10.f;
	m_bStart = false;
}

int CCloneBossBullet::Update()
{
	if (m_bDead)
		return DEAD;

	if (!m_bStart)
	{
		//시작시 클론 보스와 플레이어의 각도를 구해서 그 각으로 쭉 나아가도록 설정한다.
		float fDX = m_pTarget->GetInfo()->fX - m_tInfo.fX;
		float fDY = m_pTarget->GetInfo()->fY - m_tInfo.fY;
		float fLen = sqrtf(fDX * fDX + fDY * fDY);
		float fCeta = acosf(fDX / fLen);
		float fDegree = fCeta * (180 / PI);
		if (fDY <= 0)
		{
			fDegree = 360 - fDegree;
		}
		m_fAngle = fDegree;
		m_bStart = true;
	}
	//시작시 설정한 각도를 유지한 상태로 이동
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180));
	m_tInfo.fY += m_fSpeed * sinf(m_fAngle * (PI / 180));

	__super::Update_Rect();

	ResolveCollision();

	return NOEVENT;
}

void CCloneBossBullet::Release()
{
}

void CCloneBossBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	for (int i(0); i < m_tInfo.fCX; i++)
	{
		MoveToEx(hDC, m_tRect.left + i, m_tRect.top, nullptr);
		LineTo(hDC, m_tRect.left + i, m_tRect.bottom);
	}
}

void CCloneBossBullet::ResolveCollision()
{
	if (m_tRect.right >= WINCX) m_bDead = true; // 오른쪽 경계 닿음/초과
	if (m_tRect.left <= 0)     m_bDead = true; // 왼쪽 경계 닿음/초과
	if (m_tRect.bottom >= WINCY) m_bDead = true; // 아래 경계 닿음/초과
	if (m_tRect.top <= 0)     m_bDead = true; // 위 경계 닿음/초과
}
