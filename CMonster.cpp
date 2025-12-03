#include "pch.h"
#include "CMonster.h"
#include "CBullet.h"
#include "CAbstractFactory.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_fSpeed = 3.f;
	m_bOnLimitLine = false;
	m_dwLastShotTime = MONSTER_SHOT_COOLTIME;
	m_fDistance = 25.f;
}

int CMonster::Update()
{
	if (m_bDead)
		return DEAD;

	DWORD dwNow = GetTickCount64();

	if (m_bOnLimitLine)
	{
		if (dwNow - m_dwLastShotTime >= MONSTER_SHOT_COOLTIME)
		{
			CreateBullet();
			//마지막으로 총 쏜 시각 갱신
			m_dwLastShotTime = dwNow;
		}
	}

	m_tInfo.fY += m_fSpeed;

	__super::Update_Rect();

	//한계선 체크, 선에 닿았을 때 LimitLine true로 변경 후 총알 발사
	if (m_tRect.bottom >= MONSTER_LIMIT_LINE)
	{
		m_tInfo.fY = MONSTER_LIMIT_LINE - m_tInfo.fCX * 0.5f;
		m_fSpeed = 0.f;
		m_bOnLimitLine = true;
	}

	__super::Update_Rect();

	return NOEVENT;
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC,m_tRect.left,m_tRect.top,m_tRect.right,m_tRect.bottom);

	WCHAR cBuf[64];
	swprintf_s(cBuf, L"몬스터 남은 체력 : %d", GetLife());
	TextOutW(hDC, 10, 10, cBuf, lstrlenW(cBuf));
}

void CMonster::Release()
{
}

void CMonster::CreateBullet()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_fDistance);
	pBullet->SetDirection(eDir::DOWN);
	pBullet->SetSpeed(3.f);
	m_pBulletList->push_back(pBullet);
	return;
}

void CMonster::SetBulletDir(float fX, float fY, float fAngle)
{
	
}
