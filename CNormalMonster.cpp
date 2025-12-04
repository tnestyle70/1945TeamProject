#include "pch.h"
#include "CNormalMonster.h"
#include "CBullet.h"
#include "CAbstractFactory.h"

CNormalMonster::CNormalMonster()
{
}

CNormalMonster::~CNormalMonster()
{
}

void CNormalMonster::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	//아래를 바라보도록 설계
	m_fAngle = 270.f;
	m_fSpeed = 15.f;
	m_bOnLimitLine = false;
	m_dwLastShotTime = NORMAL_MONSTER_SHOT_COOLTIME;
	m_fDistance = 25.f;
	m_fLimitLine = 100.f;
	m_eArmor = eArmor::NORMAL_BULLET;
}

int CNormalMonster::Update()
{
	if (m_bDead)
		return DEAD;

	DWORD dwNow = GetTickCount64();

	if (m_bOnLimitLine)
	{
		if (dwNow - m_dwLastShotTime >= NORMAL_MONSTER_SHOT_COOLTIME)
		{
			CreateBullet();
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

void CNormalMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	/*
	WCHAR cBuf[64];
	swprintf_s(cBuf, L"몬스터 남은 체력 : %d", GetLife());
	TextOutW(hDC, 10, 10, cBuf, lstrlenW(cBuf));
	*/
}

void CNormalMonster::Release()
{
}

void CNormalMonster::CreateBullet()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_fDistance);
	float fDirX = cosf(m_fAngle * (PI / 180));
	float fDirY = -sinf(m_fAngle * (PI / 180));
	//pBullet->SetDirection(eDir::DOWN);
	pBullet->SetDirection(fDirX, fDirY);
	pBullet->SetSpeed(3.f);
	m_pBulletList->push_back(pBullet);
	return;
}

void CNormalMonster::SetBulletDir(float fX, float fY, float fAngle)
{

}
