#include "pch.h"
#include "CBossMonster.h"
#include "CBullet.h"
#include "CScrewBullet.h"
#include "CLeadingBullet.h"
#include "CSunFlowerBullet.h"
#include "CSpreadBullet.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CItem.h"
#include "CBossCloneMonster.h"
#include "CPlayer.h"

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
		CObj* pPlayer = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER);
		dynamic_cast<CPlayer*>(pPlayer)->UpdateScore();
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
		if (m_fLife > 350 && m_fLife <= 500)
		{
			if (dwNow - m_dwLastShotTime >= BOSS_MONSTER_SPREAD_SHOT_COOLTIME)
			{
				CreateSpreadBullet(3, 10.f);
				m_dwLastShotTime = dwNow;
			}
			if (dwNow - m_dLastSpawnTime >= BOSS_MONSTER_ORBIT_CLONE_SPAWN_COOLTIME)
			{
				CreateOrbitClone();
				m_dLastSpawnTime = dwNow;
			}
		}
		else if (m_fLife > 250 && m_fLife <= 350)
		{
			if (dwNow - m_dwLastShotTime >= BOSS_MONSTER_SPREAD_SHOT_COOLTIME)
			{
				m_fSpeed += 0.05f;
				CreateSpreadBullet(5, 20.f);
				m_dwLastShotTime = dwNow;
			}
			if (dwNow - m_dLastSpawnTime >= BOSS_MONSTER_ORBIT_CLONE_SPAWN_COOLTIME)
			{
				CreateLineClone();
				m_dLastSpawnTime = dwNow;
			}
		}
		else if (m_fLife > 150 && m_fLife <= 250)
		{
			if (dwNow - m_dwLastShotTime >= BOSS_MONSTER_SUNFLOWER_SHOT_COOLTIME)
			{
				m_fSpeed += 0.1f;
				CreateSunFlower();
				m_dwLastShotTime = dwNow;
			}
			if (dwNow - m_dLastSpawnTime >= BOSS_MONSTER_RANDOM_CLONE_SPAWN_COOLTIME)
			{
				CreateRandomClone();
				m_dLastSpawnTime = dwNow;
			}
		}
		else if (m_fLife > 0 && m_fLife <= 150)
		{
			if (dwNow - m_dwLastShotTime >= BOSS_MONSTER_SUNFLOWER_SHOT_COOLTIME)
			{
				m_fSpeed += 0.1f;
				CreateSunFlower();
				m_dwLastShotTime = dwNow;
			}
			if (dwNow - m_dLastSpawnTime >= BOSS_MONSTER_RANDOM_CLONE_SPAWN_COOLTIME)
			{
				for (int i = 0; i < 3; ++i)
				{
					CreateRandomClone();
				}
				m_dLastSpawnTime = dwNow;
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

	TCHAR szText[32];
	swprintf_s(szText, TEXT("Boss HP : %0.f"), m_fLife);
	TextOut(hDC, 440, 10, szText, lstrlen(szText));

	Rectangle(hDC, 380, 30, 380 + m_fLife / 2, 38); // 체력바

	MoveToEx(hDC, 380, 35, nullptr);
	for (int i = 0; i < m_fLife / 2; i++)
	{											//현재 체력
		MoveToEx(hDC, 380 + i, 30, nullptr);
		LineTo(hDC, 380 + i, 38);
	}

	FaceRender(hDC);
}

void CBossMonster::Release()
{
}

void CBossMonster::DropItem()
{
	eArmor eItemType = eArmor::ULTIMATE;
	//아이템 종류 결정
	int iRandItem = rand() % 5;

	CObj* pItem = CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CItem*>(pItem)->SetItemType(eItemType);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pItem);
}

void CBossMonster::CreateSunFlower()
{
	float fStartAngle = m_fAngle;
	for (int i = 0; i < 20; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSunFlowerBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(fStartAngle);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
		fStartAngle += 18.f;
	}
}

void CBossMonster::CreateSpreadBullet(int iCount, float fOffset)
{
	float fStartAngle = m_fAngle - fOffset;
	for (int i = 0; i < iCount; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSpreadBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(fStartAngle);
		fStartAngle += 10.f;
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
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
	return;
}

void CBossMonster::CreateOrbitClone()
{
	float fOrbitOffset = 0.f;
	for (int i = 0; i < 5; ++i)
	{
		float fSpawnDuration = rand() % 1000 + 2;
		CObj* pBossClone = CAbstractFactory<CBossCloneMonster>::Create(WINCX >> 1, 100.f);
		dynamic_cast<CBossCloneMonster*>(pBossClone)->SetPattern(eClonePattern::ORBIT_AND_STRIKE);
		dynamic_cast<CBossCloneMonster*>(pBossClone)->SetOrbitOffset(fOrbitOffset);
		dynamic_cast<CBossCloneMonster*>(pBossClone)->SetOrbitSpawnDuration(fSpawnDuration);
		fOrbitOffset += 72.f;
		CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS_CLONE, pBossClone);
	}
}

void CBossMonster::CreateLineClone()
{
	float fLineOffset = 78.f;
	for (int i = 0; i < 8; ++i)
	{
		float fSpawnDuration = rand() % 1000 + 2;
		CObj* pBossClone = CAbstractFactory<CBossCloneMonster>::Create(0.f + fLineOffset, 100.f);
		dynamic_cast<CBossCloneMonster*>(pBossClone)->SetPattern(eClonePattern::LINE_STRIKE);
		dynamic_cast<CBossCloneMonster*>(pBossClone)->SetLineOffset(fLineOffset);
		dynamic_cast<CBossCloneMonster*>(pBossClone)->SetLineSpawnDuration(fSpawnDuration);
		fLineOffset += 100.f;
		CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS_CLONE, pBossClone);
	}
}

void CBossMonster::CreateRandomClone()
{
	float fX = rand() % WINCX; 
	float fY = rand() % WINCY;
	CObj* pCloneBoss = CAbstractFactory<CBossCloneMonster>::Create(fX, fY);
	dynamic_cast<CBossCloneMonster*>(pCloneBoss)->SetPattern(eClonePattern::RANDOM_STRIKE);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS_CLONE, pCloneBoss);
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

void CBossMonster::FaceRender(HDC hDC)
{
	MoveToEx(hDC, m_tRect.left + 35, m_tRect.top + 50, nullptr);
	LineTo(hDC, m_tRect.left + 65, m_tRect.top + 45);					//왼쪽 눈
	LineTo(hDC, m_tRect.left + 50, m_tRect.top + 65);
	LineTo(hDC, m_tRect.left + 35, m_tRect.top + 50);


	MoveToEx(hDC, m_tRect.right - 35, m_tRect.top + 50, nullptr);
	LineTo(hDC, m_tRect.right - 65, m_tRect.top + 45);
	LineTo(hDC, m_tRect.right - 50, m_tRect.top + 65);					// 오른쪽 눈
	LineTo(hDC, m_tRect.right - 35, m_tRect.top + 50);


	MoveToEx(hDC, m_tRect.left + 73, m_tRect.top + 75, nullptr);
	LineTo(hDC, m_tRect.left + 77, m_tRect.top + 75);
	LineTo(hDC, m_tRect.left + 75, m_tRect.top + 80);
	LineTo(hDC, m_tRect.left + 73, m_tRect.top + 75);					//코


	MoveToEx(hDC, m_tRect.left + 45, m_tRect.top + 110, nullptr);
	LineTo(hDC, m_tRect.right - 45, m_tRect.top + 110);					//입


	MoveToEx(hDC, m_tRect.left + 60, m_tRect.top + 110, nullptr);
	LineTo(hDC, m_tRect.left + 65, m_tRect.top + 130);					//왼니
	LineTo(hDC, m_tRect.left + 70, m_tRect.top + 110);

	MoveToEx(hDC, m_tRect.right - 60, m_tRect.top + 110, nullptr);
	LineTo(hDC, m_tRect.right - 65, m_tRect.top + 130);					//오른니
	LineTo(hDC, m_tRect.right - 70, m_tRect.top + 110);
}