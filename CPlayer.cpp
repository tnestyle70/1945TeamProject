#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CScrewBullet.h"
#include "CSpreadBullet.h"
#include "CLeadingBullet.h"
#include "CSunFlowerBullet.h"
#include "CObjMgr.h"
#include "CShield.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX >> 1, WINCY >> 1, 50.f, 50.f };
	m_fSpeed = 10.f;
	m_fDistance = 25.f;
	m_eArmor = eArmor::NORMAL;
	m_fAngle = 90.f;
}

int CPlayer::Update()
{
	if (m_bDead)
		return DEAD;

	CObj::Update_Rect();

	Key_Input();

	return 0;
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	WCHAR cBuf[64];
	swprintf_s(cBuf, L"플레이어 남은 체력 : %d", GetLife());
	TextOutW(hDC, 10, 40, cBuf, lstrlenW(cBuf));
}

void CPlayer::Release()
{
}

void CPlayer::CreateNoramlBullet()
{

	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->SetAngle(m_fAngle);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, pBullet);
}

void CPlayer::CreateSunFlowerBullet()
{
	float fStartAngle = m_fAngle;
	for (int i = 0; i < 50; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSunFlowerBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(fStartAngle);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, pBullet);
		fStartAngle += 10.f;
	}
}

void CPlayer::CreateScrewBullet()
{
	float fStartAngle = m_fAngle;
	CObj* pBullet = CAbstractFactory<CScrewBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->SetAngle(fStartAngle);
	fStartAngle += 10.f;
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, pBullet);
	return;
}

void CPlayer::CreateSpreadBullet()
{
	float fStartAngle = 360.f - (m_fAngle + 20.f);
	for (int i = 0; i < 5; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSpreadBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(fStartAngle);
		fStartAngle += 10.f;
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, pBullet);
	}
}

void CPlayer::CreateLeadingBullet()
{
	CObj* pLeadingBullet = CAbstractFactory<CLeadingBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, pLeadingBullet);
}

void CPlayer::CreateShield()
{
	CObj* pShield = CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY);
	pShield->SetAngle(m_fAngle);
	CObjMgr::Get_Instance()->Add_Object(OBJ_SHIELD, pShield);
}

void CPlayer::Key_Input()
{
	if (GetAsyncKeyState('1')) 
		CreateShield();

	if (GetAsyncKeyState('2'))
		m_eArmor = eArmor::LEADING;

	if (GetAsyncKeyState('3'))
		m_eArmor = eArmor::SUNFLOWER;

	if (GetAsyncKeyState(VK_RIGHT))	{	m_tInfo.fX += m_fSpeed;	}
	if (GetAsyncKeyState(VK_LEFT))	{ m_tInfo.fX -= m_fSpeed; }
	if (GetAsyncKeyState(VK_UP))	{ m_tInfo.fY -= m_fSpeed; }
	if (GetAsyncKeyState(VK_DOWN))	{ m_tInfo.fY += m_fSpeed; }

	if (GetAsyncKeyState(VK_SPACE)) 
	{
		DWORD dwNow = GetTickCount64();

		if (dwNow - m_dwLastShotTime >= PLAYER_SHOT_COOLTIME)
		{
			switch (m_eArmor)
			{
			case NORMAL:
				CreateScrewBullet();
				m_dwLastShotTime = dwNow;
				break;
			case SPREAD:
				CreateSunFlowerBullet();
				m_dwLastShotTime = dwNow;
				break;
			case SCREW:
				CreateSpreadBullet();
				m_dwLastShotTime = dwNow;
				break;
			case LEADING:
				CreateSpreadBullet();
				m_dwLastShotTime = dwNow;
				break;
			case SUNFLOWER:
				CreateLeadingBullet();
				m_dwLastShotTime = dwNow;
				break;
			default:
				break;
			}
		}
		else
			return;
	}
}
