#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CLeadingBullet.h"

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
	m_eArmor = eArmor::NORMAL_BULLET;
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
	pBullet->SetDirection(eDir::UP);
	pBullet->SetSpeed(10.f);
	m_pBulletList->push_back(pBullet);
}

void CPlayer::CreateSpreadBullet()
{
}

void CPlayer::CreateLeadingBullet()
{
	CObj* pLeadingBullet = CAbstractFactory<CLeadingBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pLeadingBullet->SetTargetMonster(this->GetMonsterListTarget());
	m_pBulletList->push_back(pLeadingBullet);
}

void CPlayer::Key_Input()
{
	if (GetAsyncKeyState(VK_RIGHT))	{	m_tInfo.fX += m_fSpeed;	}
	if (GetAsyncKeyState(VK_LEFT))	{ m_tInfo.fX -= m_fSpeed; }
	if (GetAsyncKeyState(VK_UP))	{ m_tInfo.fY -= m_fSpeed; }
	if (GetAsyncKeyState(VK_DOWN))	{ m_tInfo.fY += m_fSpeed; }
	if (GetAsyncKeyState(VK_SPACE)) 
	{
		DWORD dwNow = GetTickCount64();

		if (dwNow - m_dwLastShotTime >= PLAYER_SHOT_COOLTIME)
		{
			CreateLeadingBullet();
			//마지막으로 총 쏜 시각 갱신
			m_dwLastShotTime = dwNow;
		}
		else
			return;
	}
}
