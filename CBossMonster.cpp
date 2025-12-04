#include "pch.h"
#include "CBossMonster.h"
#include "CBullet.h"
#include "CScrewBullet.h"
#include "CSunFlowerBullet.h"
#include "CSpreadBullet.h"
#include "CAbstractFactory.h"

CBossMonster::CBossMonster()
{
}

CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;
	m_fSpeed = 3.f;
	m_bOnLimitLine = false;
	m_dwLastShotTime = BOSS_MONSTER_SUNFLOWER_SHOT_COOLTIME;
	m_fDistance = 75.f;
	m_fLimitLine = 500.f;
	m_fAngle = 20.f;
	m_fSpread = 20.f;
	m_eArmor = eArmor::NORMAL_BULLET;
}

int CBossMonster::Update()
{
	if (m_bDead)
		return DEAD;

	DWORD dwNow = GetTickCount64();



	if (m_bOnLimitLine)
	{
		if (m_iLife > 950 && m_iLife <= 1000)
		{
			if (dwNow - m_dwLastShotTime >= BOSS_MONSTER_SPREAD_SHOT_COOLTIME)
			{
				CreateSpreadBullet();
				m_fAngle += 30;
				m_dwLastShotTime = dwNow;
			}
		}
		else if (m_iLife >= 600 && m_iLife <= 800)
		{
			if (dwNow - m_dwLastShotTime >= BOSS_MONSTER_SUNFLOWER_SHOT_COOLTIME)
			{
				CreateSunFlower();
				m_dwLastShotTime = dwNow;
			}
		}
		else if (m_iLife >= 600 && m_iLife <= 800)
		{
			if (dwNow - m_dwLastShotTime >= BOSS_MONSTER_SUNFLOWER_SHOT_COOLTIME)
			{
				CreateSunFlower();
				m_dwLastShotTime = dwNow;
			}
		}
		//SetBossDirection();
		m_tInfo.fX += m_fSpeed * m_fDirX;
		m_tInfo.fY += m_fSpeed * m_fDirY;
		//ResolveCollision();
	}

	//한계선 체크, 선에 닿았을 때 LimitLine true로 변경 후 총알 발사
	if (m_tRect.bottom >= m_fLimitLine)
	{
		m_tInfo.fY = m_fLimitLine - m_tInfo.fCX * 0.5f;
		m_fSpeed = 0.f;
		m_bOnLimitLine = true;
	}

	m_tInfo.fY += m_fSpeed;

	__super::Update_Rect();

	return NOEVENT;
}

void CBossMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	WCHAR cBuf[64];
	swprintf_s(cBuf, L"보스 몬스터 남은 체력 : %d", GetLife());
	TextOutW(hDC, 10, 10, cBuf, lstrlenW(cBuf));
}

void CBossMonster::Release()
{
}

void CBossMonster::CreateSunFlower()
{
	float fStartAngle = m_fAngle;
	for (int i = 0; i < 50; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSunFlowerBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(fStartAngle);
		m_pBulletList->push_back(pBullet);
		fStartAngle += 10.f;
	}
}

void CBossMonster::CreateSpreadBullet()
{
	for (int i = 0; i < 5; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSpreadBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(m_fAngle);
		m_fAngle -= 10.f;
		//pBullet->SetTarget(this->GetTarget());
		m_pBulletList->push_back(pBullet);
	}
}

void CBossMonster::CreateScrewBullet()
{
	CObj* pBullet = CAbstractFactory<CScrewBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->SetAngle(m_fAngle);
	m_fAngle += 10.f;
	pBullet->SetTarget(this->GetTarget());
	m_pBulletList->push_back(pBullet);
	return;
}

void CBossMonster::CreateBullet()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_fDistance);
	float fDirX = cosf(m_fAngle * (PI / 180));
	float fDirY = -sinf(m_fAngle * (PI / 180));
	pBullet->SetSpeed(3.f);
	pBullet->SetDirection(fDirX, fDirY);
	m_pBulletList->push_back(pBullet);
	return;
}

void CBossMonster::SetBulletDir()
{
	m_fDirX = cosf(m_fAngle * (PI / 180));
	m_fDirY = -sinf(m_fAngle * (PI / 180));
}

void CBossMonster::SetBossDirection()
{
	m_fDirX = cosf(m_fAngle * (PI / 180));
	m_fDirY = -sinf(m_fAngle * (PI / 180));
}

void CBossMonster::ResolveCollision()
{
	if (m_tRect.right <= WINCX - 10.f)
	{
		m_fAngle = 90.f;
	}
}
