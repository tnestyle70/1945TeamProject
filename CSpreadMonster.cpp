#include "pch.h"
#include "CSpreadMonster.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CSpreadBullet.h"
#include "CObjMgr.h"

CSpreadMonster::CSpreadMonster()
{
}

CSpreadMonster::~CSpreadMonster()
{
}

void CSpreadMonster::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;
	m_fSpeed = 3.f;
	m_bOnLimitLine = false;
	m_dwLastShotTime = NORMAL_MONSTER_SHOT_COOLTIME;
	m_fDistance = 25.f;
	m_fLimitLine = 500.f;
}

int CSpreadMonster::Update()
{
	if (m_bDead)
		return DEAD;

	DWORD dwNow = GetTickCount64();

	if (m_bOnLimitLine)
	{
		if (dwNow - m_dwLastShotTime >= NORMAL_MONSTER_SHOT_COOLTIME)
		{
			CreateSunFlower();
			//마지막으로 총 쏜 시각 갱신
			m_dwLastShotTime = dwNow;
		}
	}

	m_tInfo.fY += m_fSpeed;

	__super::Update_Rect();

	//한계선 체크, 선에 닿았을 때 LimitLine true로 변경 후 총알 발사
	if (m_tRect.bottom >= m_fLimitLine)
	{
		m_tInfo.fY = m_fLimitLine - m_tInfo.fCX * 0.5f;
		m_fSpeed = 0.f;
		m_bOnLimitLine = true;
	}

	__super::Update_Rect();

	return NOEVENT;
}

void CSpreadMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	WCHAR cBuf[64];
	swprintf_s(cBuf, L"보스 몬스터 남은 체력 : %d", GetLife());
	TextOutW(hDC, 10, 10, cBuf, lstrlenW(cBuf));
}

void CSpreadMonster::Release()
{
}

void CSpreadMonster::CreateSunFlower()
{
	const int iBulletCount = 16;
	const float fBaseAngle = 0.f;
	const float fAngleStep = 360.f / iBulletCount;

	for (int i = 0; i < iBulletCount; ++i)
	{
		float fAngleDeg = fBaseAngle + fAngleStep * i;

		m_fDirX = cosf(fAngleDeg * (PI / 180.f));
		m_fDirY = -sinf(fAngleDeg * (PI / 180.f));

		CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetDirection(m_fDirX, m_fDirY);
	}
}

void CSpreadMonster::CreateSpiralBullet()
{
}

void CSpreadMonster::CreateBullet()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_fDistance);
	pBullet->SetDirection(eDir::DOWN);
	pBullet->SetSpeed(3.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
	return;
}

void CSpreadMonster::SetBulletDir(float fX, float fY, float fAngle)
{

}
