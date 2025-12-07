#include "pch.h"
#include "CNormalMonster.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CItem.h"
#include "CPlayer.h"

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
	m_bDropItem = false;
}

int CNormalMonster::Update()
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
			CreateBullet();
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

void CNormalMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CNormalMonster::Release()
{
}

void CNormalMonster::DropItem()
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

void CNormalMonster::CreateBullet()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_fDistance);
	pBullet->SetAngle(m_fAngle);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
	return;
}

void CNormalMonster::SetBulletDir(float fX, float fY, float fAngle)
{

}
