#include "pch.h"
#include "CShield.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CBullet.h"

CShield::CShield()
{
}

CShield::~CShield()
{
}

void CShield::Initialize()
{
	m_fSpeed = 6.f;
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_fDistance = 100.f;
}

int CShield::Update()
{
	if (m_bDead)
		return DEAD;

	m_pTarget = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER);

	m_tInfo.fX = m_pTarget->GetInfo()->fX + m_fDistance * cosf(m_fAngle * (PI / 180));
	m_tInfo.fY = m_pTarget->GetInfo()->fY - m_fDistance * sinf(m_fAngle * (PI / 180));

	m_fAngle += 3.f;

	__super::Update_Rect();

	return NOEVENT;
}

void CShield::Release()
{
}

void CShield::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CShield::TryParry(float fAngle)
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	//Bullet의 Angle을 기준으로 총알을 발사
	pBullet->SetAngle(fAngle);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, pBullet);
}
