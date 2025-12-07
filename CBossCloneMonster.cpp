#include "pch.h"
#include "CBossCloneMonster.h"
#include "CObjMgr.h"
#include "CCloneBossBullet.h"
#include "CAbstractFactory.h"
#include "CBullet.h"

CBossCloneMonster::CBossCloneMonster()
{
}

CBossCloneMonster::~CBossCloneMonster()
{
}

void CBossCloneMonster::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_eState = eCloneState::APPEAR;
	//원형 회전 패턴
	m_fOrbitOffset = 0.f;
	m_fOrbitAngle = 0.f;
	m_fOrbitDistance = 80.f;
	m_fOrbitAppearDuration = 1000.f;
	m_fAimDuration = 100.f;
	m_fVanishDuration = 1000.f;
	m_bStart = false;
	m_bShot = false;
	//라인 패턴
	m_fLineSpawnDuration = 0.f;
	//랜덤 스폰 패턴
	m_fRandomAppearDuration = 100.f;
}

int CBossCloneMonster::Update()
{
	if (m_bDead)
		return DEAD;

	UpdatePhase();
	
	__super::Update_Rect();

	return NOEVENT;
}

void CBossCloneMonster::UpdatePhase()
{
	switch (m_ePattern)
	{
	case eClonePattern::ORBIT_AND_STRIKE:
		UpdateOrbitAndAttack();
		break;
	case eClonePattern::LINE_STRIKE:
		UpdateLineStrike();
		break;
	case eClonePattern::RANDOM_STRIKE:
		UpdateRandomStrike();
		break;
	default:
		break;
	}
}

void CBossCloneMonster::UpdateOrbitAndAttack()
{
	DWORD dwNow = GetTickCount64();

	switch (m_eState)
	{
	case eCloneState::APPEAR:
		m_dwAppearanceTime = GetTickCount64();
		m_eState = eCloneState::AIM;
		break;
	case eCloneState::AIM:
		UpdateOrbitMove();

		if (dwNow - m_dwAppearanceTime >= m_fOrbitAppearDuration)
		{
			m_eState = eCloneState::SHOT;
		}
		break;
	case eCloneState::SHOT:
		CreateBullet();
		m_eState = eCloneState::VANISH;
		m_dwAppearanceTime = GetTickCount64();
		break;
	case eCloneState::VANISH:
		if (dwNow - m_dwAppearanceTime >= m_fVanishDuration)
		{
			m_bDead = true;
		}
		break;
	default:
		break;
	}
}

void CBossCloneMonster::UpdateOrbitMove()
{
	if (!m_bStart)
	{
		//초기 중심값 설정
		m_fCenterX = m_tInfo.fX;
		m_fCenterY = m_tInfo.fY;
		//생성할 때 오프셋만큼 초기 각도값에 더해줌
		m_fOrbitAngle += m_fOrbitOffset;
		m_bStart = true;
	}
	//원 궤적 따라서 이동
	m_tInfo.fX = m_fCenterX + m_fOrbitDistance * cosf(m_fOrbitAngle * (PI / 180));
	m_tInfo.fY = m_fCenterY - m_fOrbitDistance * sinf(m_fOrbitAngle * (PI / 180));

	m_fOrbitAngle += 3.f;
}

void CBossCloneMonster::UpdateLineStrike()
{
	DWORD dwNow = GetTickCount64();

	switch (m_eState)
	{
	case eCloneState::APPEAR:
		m_dwAppearanceTime = GetTickCount64();
		m_eState = eCloneState::AIM;
		break;
	case eCloneState::AIM:
		if (dwNow - m_dwAppearanceTime >= m_fLineSpawnDuration)
		{
			m_eState = eCloneState::SHOT;
		}
		break;
	case eCloneState::SHOT:
		CreateBullet();
		m_eState = eCloneState::VANISH;
		m_dwAppearanceTime = GetTickCount64();
		break;
	case eCloneState::VANISH:
		if (dwNow - m_dwAppearanceTime >= m_fVanishDuration)
		{
			m_bDead = true;
		}
		break;
	default:
		break;
	}
}

void CBossCloneMonster::UpdateRandomStrike()
{
	DWORD dwNow = GetTickCount64();

	switch (m_eState)
	{
	case eCloneState::APPEAR:
		m_dwAppearanceTime = GetTickCount64();
		m_eState = eCloneState::SHOT;
		break;
	case eCloneState::AIM:
		if (dwNow - m_dwAppearanceTime >= m_fRandomAppearDuration)
		{
			m_eState = eCloneState::SHOT;
		}
		break;
	case eCloneState::SHOT:
		CreateBullet();
		m_eState = eCloneState::VANISH;
		m_dwAppearanceTime = GetTickCount64();
		break;
	case eCloneState::VANISH:
		if (dwNow - m_dwAppearanceTime >= m_fVanishDuration)
		{
			m_bDead = true;
		}
		break;
	default:
		break;
	}
}


void CBossCloneMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBossCloneMonster::Release()
{
}

void CBossCloneMonster::CreateBullet()
{
	CObj* pBullet = CAbstractFactory<CCloneBossBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->SetTarget(CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
}