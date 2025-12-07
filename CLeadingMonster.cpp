#include "pch.h"
#include "CLeadingMonster.h"
#include "CBullet.h"
#include "CSunFlowerBullet.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CLeadingMonster::CLeadingMonster()
{
}

CLeadingMonster::~CLeadingMonster()
{
}

void CLeadingMonster::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;
	m_fSpeed = 3.f;
	m_bOnLimitLine = false;
	m_dwLastShotTime = NORMAL_MONSTER_SHOT_COOLTIME;
	m_fDistance = 25.f;
	m_fLimitLine = 500.f;
}

int CLeadingMonster::Update()
{
	if (m_bDead)
		return DEAD;

	DWORD dwNow = GetTickCount64();

	if (m_bOnLimitLine)
	{
		if (dwNow - m_dwLastShotTime >= NORMAL_MONSTER_SHOT_COOLTIME)
		{
			CreateSunFlower();
			//마지막으로 총 쏜 시각 갱신
			m_dwLastShotTime = dwNow;
		}
	}

	__super::Update_Rect();

	//한계선 체크, 선에 닿았을 때 LimitLine true로 변경 후 총알 발사
	if (m_tRect.bottom >= m_fLimitLine)
	{
		m_bOnLimitLine = true;
		m_pTarget = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER);
		float fDX = m_pTarget->GetInfo()->fX - m_tInfo.fX;
		float fDY = m_pTarget->GetInfo()->fY - m_tInfo.fY;
		float fDistance = sqrtf(fDX * fDX + fDY * fDY);
		float fCeta = acosf(fDX / fDistance);
		float fDegree = fCeta * (180 / PI);
		m_tInfo.fX += m_fSpeed * cosf(fDegree * (PI / 180));
		m_tInfo.fY += m_fSpeed * sinf(fDegree * (PI / 180));
	}
	else
	{
		m_tInfo.fY += m_fSpeed;
	}

	__super::Update_Rect();

	return NOEVENT;
}

void CLeadingMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CLeadingMonster::Release()
{
}

void CLeadingMonster::CreateSunFlower()
{
	//반드시 StartAngle 변수를 생성해야 함. 몬스터는 Angle을 기준으로 움직이기 때문에 
	//몬스터 angle 값을 변화 시키게 되면 몬스터의 방향이 계속 틀어짐
	float fStartAngle = m_fAngle;

	for (int i = 0; i < 50; ++i)
	{
		CObj* pBullet = CAbstractFactory<CSunFlowerBullet>::Create(m_tInfo.fX, m_tInfo.fY);
		pBullet->SetAngle(fStartAngle);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
		fStartAngle += 10.f;
	}
}

void CLeadingMonster::CreateSpiralBullet()
{
}

void CLeadingMonster::CreateBullet()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_fDistance);
	pBullet->SetDirection(eDir::DOWN);
	pBullet->SetSpeed(3.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBullet);
	return;
}

void CLeadingMonster::SetBulletDir(float fX, float fY, float fAngle)
{

}
