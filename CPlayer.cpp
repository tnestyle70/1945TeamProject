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
	m_tInfo = { WINCX >> 1, WINCY >> 1, 40.f, 60.f };
	m_fSpeed = 10.f;
	m_fDistance = 25.f;
	m_eArmor = eArmor::NORMAL;
	m_fAngle = 90.f;
	m_fLife = 50;
	m_fMaxLife = 50;
	m_iScore = 0;
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
	/*
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
		*/

	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY - 15, nullptr);
	LineTo(hDC, m_tInfo.fX + 10, m_tInfo.fY);
	LineTo(hDC, m_tInfo.fX - 10, m_tInfo.fY);
	LineTo(hDC, m_tInfo.fX, m_tInfo.fY - 15);

	// 몸체
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX, m_tInfo.fY + 22);

	// 좌 날개
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY + 7, nullptr);
	LineTo(hDC, m_tInfo.fX - 20, m_tInfo.fY + 15);

	// 우 날개
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY + 7, nullptr);
	LineTo(hDC, m_tInfo.fX + 20, m_tInfo.fY + 15);

	// 꼬리 
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY + 22, nullptr);
	LineTo(hDC, m_tInfo.fX - 10, m_tInfo.fY + 30);
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY + 22, nullptr);
	LineTo(hDC, m_tInfo.fX + 10, m_tInfo.fY + 30);
	LineTo(hDC, m_tInfo.fX - 10, m_tInfo.fY + 30);

	TCHAR szText[32];
	swprintf_s(szText, TEXT("HP : %0.f"), m_fLife);
	TextOut(hDC, 10, 10, szText, lstrlen(szText));

	Rectangle(hDC, 10, 30, 10 + m_fMaxLife * 4, 40); // 체력바

	MoveToEx(hDC, 10, 30, nullptr);
	for (int i = 0; i < m_fLife * 4; i++)
	{											//현재 체력
		MoveToEx(hDC, 10 + i, 30, nullptr);
		LineTo(hDC, 10 + i, 40);
	}

	swprintf_s(szText, TEXT("SCORE : %d"), m_iScore);
	TextOut(hDC, 10, 50, szText, lstrlen(szText));
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
	for (int i = 0; i < 20; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSunFlowerBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(fStartAngle);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, pBullet);
		fStartAngle += 18.f;
	}
}

void CPlayer::CreateScrewBullet()
{
	float fStartAngle = m_fAngle - 10.f;
	CObj* pBullet = CAbstractFactory<CScrewBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->SetAngle(fStartAngle);
	fStartAngle += 10.f;
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, pBullet);
	return;
}

void CPlayer::CreateSpreadBullet()
{
	float fStartAngle = m_fAngle + 10.f;
	for (int i = 0; i < 3; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSpreadBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(fStartAngle);
		fStartAngle -= 10.f;
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, pBullet);
	}
}

void CPlayer::CreateLeadingBullet()
{
	CObj* pLeadingBullet = CAbstractFactory<CLeadingBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, pLeadingBullet);
}

void CPlayer::CreateUltimate()
{
	for (int i = 0; i < 1000; ++i)
	{
		float fRandX = rand() % WINCX;
		float fRandY = rand() % WINCY;
		CObj* pBullet = CAbstractFactory<CBullet>::Create(fRandX, fRandY);
		pBullet->SetAngle(m_fAngle);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, pBullet);
	}
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
				CreateNoramlBullet();
				m_dwLastShotTime = dwNow;
				break;
			case SPREAD:
				CreateSpreadBullet();
				m_dwLastShotTime = dwNow;
				break;
			case SCREW:
				CreateScrewBullet();
				m_dwLastShotTime = dwNow;
				break;
			case LEADING:
				CreateLeadingBullet();
				m_dwLastShotTime = dwNow;
				break;
			case SUNFLOWER:
				CreateSunFlowerBullet();
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
