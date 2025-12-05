#include "pch.h"
#include "CObjMgr.h"
#include "CLeadingBullet.h"

CLeadingBullet::CLeadingBullet()
{
	m_pNearMonster = nullptr;
}

CLeadingBullet::~CLeadingBullet()
{
}

void CLeadingBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fSpeed = 10.f; //속도 초기화
}

int CLeadingBullet::Update() //Bullet은 상태만 변화, 판단은 MainGame에서 내리기
{
	if (m_bDead)
		return DEAD;

	m_pNearMonster = FindNearestMonster();
	if (!m_pNearMonster || m_pNearMonster->IsDead())
		return NOEVENT;
	else
	{
		float fDX = m_pNearMonster->GetInfo()->fX - m_tInfo.fX;
		float fDY = m_pNearMonster->GetInfo()->fY - m_tInfo.fY;
		//빗변 구하기
		float fDistance = sqrtf(fDX * fDX + fDY * fDY);

		float fCeta = acosf(fDX / fDistance);
		float fDegree = fCeta * (180 / PI);

		if (fDY <= 0)
		{
			fDegree = 360 - fDegree;
		}
		//구한 세타값을 기준으로 이동
		m_tInfo.fX += m_fSpeed * cosf(fDegree * (PI / 180));
		m_tInfo.fY += m_fSpeed * sinf(fDegree * (PI / 180));
	}

	CObj::Update_Rect();

	return NOEVENT;
}

void CLeadingBullet::Release()
{
}

void CLeadingBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

CObj* CLeadingBullet::FindNearestMonster()
{
	list<CObj*>* plistMonster = CObjMgr::Get_Instance()->Get_Object_List(OBJ_MONSTER);

	float fNearnestDist = 1000000.f;

	for (auto iter = plistMonster->begin();
		iter != plistMonster->end();)
	{
		CObj* pMonster = (*iter);
		float fDX = pMonster->GetInfo()->fX - m_tInfo.fX;
		float fDY = pMonster->GetInfo()->fY - m_tInfo.fY;
		float fLen = sqrtf(fDX * fDX + fDY * fDY);
		if (fNearnestDist >= fLen)
		{
			fNearnestDist = fLen;
			iter++;
			continue;
		}
		else
			iter++;
	}
	if (fNearnestDist == 1000000.f)
	{
		return nullptr;
	}
	else
	{
		for (auto iter = plistMonster->begin();
			iter != plistMonster->end();)
		{
			CObj* pMonster = (*iter);
			float fDX = pMonster->GetInfo()->fX - m_tInfo.fX;
			float fDY = pMonster->GetInfo()->fY - m_tInfo.fY;
			float fLen = sqrtf(fDX * fDX + fDY * fDY);
			if (fNearnestDist == fLen)
			{
				return pMonster;
			}
			else
				iter++;
		}
	}
}
