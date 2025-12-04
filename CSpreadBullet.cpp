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
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
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

	return NOEVENT;
}

void CSpreadBullet::Release()
{
}

void CSpreadBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
