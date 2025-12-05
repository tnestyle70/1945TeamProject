#include "pch.h"
#include "CBossMonster.h"
#include "CBullet.h"
#include "CScrewBullet.h"
#include "CSunFlowerBullet.h"
#include "CSpreadBullet.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CItem.h"

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
	m_fSpeed = 5.f;
	m_bOnLimitLine = false;
	m_dwLastShotTime = BOSS_MONSTER_SUNFLOWER_SHOT_COOLTIME;
	m_fDistance = 75.f;
	m_fLimitLine = 500.f;
	m_fAngle = 20.f;
	m_fSpread = 20.f;
	m_eArmor = eArmor::NORMAL;
	m_bDropItem = false;
}

int CBossMonster::Update()
{
	if (m_bDead)
	{
		if (!m_bDropItem)
		{
			DropItem();
			m_bDropItem = true;
		}
		return DEAD;
	}

	DWORD dwNow = GetTickCount64();

	if (m_bOnLimitLine)
	{
		m_fLimitLine = 10000.f;
		if (m_iLife > 950 && m_iLife <= 1000)
		{
			if (dwNow - m_dwLastShotTime >= BOSS_MONSTER_SCREW_SHOT_COOLTIME)
			{
				CreateBullet();
				m_dwLastShotTime = dwNow;
			}
		}
		else if (m_iLife >= 900 && m_iLife <= 950)
		{
			if (dwNow - m_dwLastShotTime >= BOSS_MONSTER_SUNFLOWER_SHOT_COOLTIME)
			{
				m_fSpeed += 5.f;
				CreateSunFlower();
				m_dwLastShotTime = dwNow;
			}
		}
		else if (m_iLife >= 600 && m_iLife <= 900)
		{
			if (dwNow - m_dwLastShotTime >= BOSS_MONSTER_SUNFLOWER_SHOT_COOLTIME)
			{
				m_fSpeed += 5.f;
				CreateScrewBullet();
				m_dwLastShotTime = dwNow;
			}
		}
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180));
		ResolveCollision();
		//SetBossDirection();
		//m_tInfo.fX += m_fSpeed * m_fDirX;
		//m_tInfo.fY += m_fSpeed * m_fDirY;
		//ResolveCollision();
	}
	if (!m_bOnLimitLine)
	{
		m_tInfo.fY += m_fSpeed;
	}
	//한계선 체크, 선에 닿았을 때 LimitLine true로 변경 후 총알 발사
	if (m_tRect.bottom >= m_fLimitLine)
	{
		m_tInfo.fY = m_fLimitLine - m_tInfo.fCX * 0.5f;
		m_bOnLimitLine = true;
	}
	
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

void CBossMonster::DropItem()
{
	CObj* pItem = CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pItem);
}

void CBossMonster::CreateSunFlower()
{
	float fStartAngle = m_fAngle;
	for (int i = 0; i < 50; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSunFlowerBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(fStartAngle);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
		fStartAngle += 10.f;
	}
}

void CBossMonster::CreateSpreadBullet()
{
	float fStartAngle = m_fAngle;
	for (int i = 0; i < 5; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSpreadBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(fStartAngle);
		fStartAngle -= 10.f;
		pBullet->SetTarget(CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
		//m_pBulletList->push_back(pBullet);
	}
}

void CBossMonster::CreateScrewBullet()
{
	float fStartAngle = m_fAngle;
	CObj* pBullet = CAbstractFactory<CScrewBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->SetAngle(fStartAngle);
	fStartAngle += 10.f;
	pBullet->SetTarget(CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
	return;
}

void CBossMonster::CreateBullet()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_fDistance);
	float fDirX = cosf(m_fAngle * (PI / 180));
	float fDirY = -sinf(m_fAngle * (PI / 180));
	pBullet->SetSpeed(3.f);
	pBullet->SetDirection(fDirX, fDirY);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
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
	float fRandAngle;
	if (m_tRect.right >= WINCX)
	{
		m_tInfo.fX -= 10.f;
		fRandAngle = rand() % 360;
		m_fAngle = fRandAngle;
	}
	if (m_tRect.left <= 0)
	{
		m_tInfo.fX += 10.f;
		fRandAngle = rand() % 360;
		m_fAngle = fRandAngle;
	}
	if (m_tRect.top <= 0)
	{
		m_tInfo.fY += 10.f;
		fRandAngle = rand() % 360;
		m_fAngle = fRandAngle;
	}
	if (m_tRect.bottom >= WINCY)
	{
		m_tInfo.fY -= 10.f;
		fRandAngle = rand() % 360;
		m_fAngle = fRandAngle;
	}
}
