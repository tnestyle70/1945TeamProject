#include "pch.h"
#include "CSpreadMonster.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CSpreadBullet.h"
#include "CObjMgr.h"
#include "CItem.h"
#include "CPlayer.h"

CSpreadMonster::CSpreadMonster()
{
}

CSpreadMonster::~CSpreadMonster()
{
}

void CSpreadMonster::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;;
	m_fSpeed = 3.f;
	m_bOnLimitLine = false;
	m_dwLastShotTime = NORMAL_MONSTER_SHOT_COOLTIME;
	m_fDistance = 25.f;
	m_fAngle = 90.f;
	m_bDropItem = false;
}

int CSpreadMonster::Update()
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
		if (dwNow - m_dwLastShotTime >= NORMAL_MONSTER_SHOT_COOLTIME)
		{
			CreateSpread();
			//마지막으로 총 쏜 시각 갱신
			m_dwLastShotTime = dwNow;
		}
	}

	__super::Update_Rect();

	//한계선 체크, 선에 닿았을 때 LimitLine true로 변경 후 총알 발사
	if (m_tRect.bottom >= m_fLimitLine)
	{
		m_tInfo.fY = m_fLimitLine - m_tInfo.fCX * 0.5f;
		m_fSpeed = 0.f;
		m_bOnLimitLine = true;
	}
	else
	{
		m_tInfo.fY += m_fSpeed;
	}

	__super::Update_Rect();

	return NOEVENT;
}

void CSpreadMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CSpreadMonster::Release()
{
}

void CSpreadMonster::DropItem()
{
	eArmor eItemType = eArmor::NORMAL;
	//아이템 종류 결정
	int iRandItem = rand() % 5;

	switch (iRandItem)
	{
	case 0: eItemType = eArmor::SPREAD; break;
	case 1: eItemType = eArmor::LEADING; break;
	case 2: eItemType = eArmor::SCREW; break;
	case 3: eItemType = eArmor::SUNFLOWER; break;
	case 4: eItemType = eArmor::SHIELD; break;
	default:
		break;
	}

	int iRandDrop = rand() % 100;

	if (iRandDrop <= 30)
		return;
	CObj* pItem = CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CItem*>(pItem)->SetItemType(eItemType);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pItem);
}

void CSpreadMonster::CreateSpread()
{
	float fStartAngle = m_fAngle - 10.f;
	for (int i = 0; i < 3; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSpreadBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(fStartAngle);
		fStartAngle += 10.f;
		pBullet->SetTarget(CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
		//m_pBulletList->push_back(pBullet);
	}
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
