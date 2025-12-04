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
	m_fSpeed = 10.f; //속도 초기화
	m_fDistance = 30.f;//총알과 중심으로 회전할 반지름 사이의 거리
	m_fRotateAngle = 15.f;
	m_fRotateSpeed = 20.f;
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
	float fDX = m_pTarget->GetInfo()->fX - m_tInfo.fX;
	float fDY = m_pTarget->GetInfo()->fY - m_tInfo.fY;
	//빗변 구하기
	float fDistance = sqrtf(fDX * fDX + fDY * fDY);

	float fCeta = acosf(fDX / fDistance);
	float fDegree = fCeta * (180 / PI);

	if (fDY <= 0)
	{
		fDegree = 360 - fDegree;
	}
	//구한 세타값을 기준으로 이동
	m_tCenter.x += m_fSpeed * cosf(fDegree * (PI / 180));
	m_tCenter.y += m_fSpeed * sinf(fDegree * (PI / 180));

	m_fRotateAngle += m_fRotateSpeed;

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
