#include "pch.h"
#include "CScrewBullet.h"

CScrewBullet::CScrewBullet() : m_bStart(true), m_fRotateAngle(0.f), m_fRotateSpeed(0.f)
{
	ZeroMemory(&m_tCenter, 0, sizeof(m_tCenter));
}

CScrewBullet::~CScrewBullet()
{
}

void CScrewBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fSpeed = 5.f; //속도 초기화
	m_fDistance = 50.f;//총알과 중심으로 회전할 반지름 사이의 거리
	m_fRotateAngle = 10.f;
	m_fRotateSpeed = 10.f;
}

int CScrewBullet::Update() //Bullet은 상태만 변화, 판단은 MainGame에서 내리기
{
	if (m_bDead)
		return DEAD;

	if (m_bStart)
	{
		//몬스터를 기준으로 발사 위치 설정 
		m_tCenter.x = m_tInfo.fX + m_fDistance;
		m_tCenter.y = m_tInfo.fY + m_fDistance;
		m_bStart = false;
	}
	//기존 총알 로직대로 이동
	m_tCenter.x += m_fSpeed * cosf(m_fAngle * (PI / 180));
	m_tCenter.y -= m_fSpeed * sinf(m_fAngle * (PI / 180));

	m_fRotateAngle += m_fRotateSpeed;
	//총알은 rotate와 center를 중심으로 공전하며 이동
	m_tInfo.fX = m_tCenter.x + m_fDistance * cosf(m_fRotateAngle * (PI / 180.f));
	m_tInfo.fY = m_tCenter.y - m_fDistance * sinf(m_fRotateAngle * (PI / 180.f));

	CObj::Update_Rect();

	return NOEVENT;
}

void CScrewBullet::Release()
{
}

void CScrewBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
