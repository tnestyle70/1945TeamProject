#include "pch.h"
#include "CCollisionMgr.h"

void CCollisionMgr::PlayerBulletCollide(list<CObj*> PlayerBullet, list<CObj*> Monster)
{
	RECT rc = {};
	for (auto& pPlayerBullet : PlayerBullet)
	{
		for (auto& pMonster : Monster)
		{
			if (IntersectRect(&rc, pPlayerBullet->GetRect(), pMonster->GetRect()))
			{
				pMonster->GetDamage();
				if (pMonster->GetLife() <= 0)
				{
					pMonster->SetDead();
				}
			}
		}
	}
}

void CCollisionMgr::MonsterBulletCollide(list<CObj*> MonsterBullet, list<CObj*> Player)
{
	RECT rc = {};
	for (auto& pMonsterBullet : MonsterBullet)
	{
		for (auto& pPlayer : Player)
		{
			if (IntersectRect(&rc, pMonsterBullet->GetRect(), pPlayer->GetRect()))
			{
				pPlayer->GetDamage();
				if (pPlayer->GetLife() <= 0)
				{
					pPlayer->SetDead();
				}
			}
		}
	}
}

void CCollisionMgr::CircleCollide(list<CObj*> Dst, list<CObj*> Src)
{
	for (auto& pDst : Dst)
	{
		for (auto& pSrc : Src)
		{
			if (CheckCircle(pDst, pSrc))
			{
				pDst->SetDead();
				pSrc->SetDead();
			}
		}
	}
}

bool CCollisionMgr::CheckCircle(CObj* pDst, CObj* pSrc)
{
	//몬스터와 총알 중심 사이의 거리와 각각의 반지름을 더한 값을 비교한다. 
	float fWidth = fabs(pDst->GetInfo()->fX - pSrc->GetInfo()->fX);
	float fHeight = fabs(pDst->GetInfo()->fY - pSrc->GetInfo()->fY);
	float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float fRadius = (pDst->GetInfo()->fCX + pSrc->GetInfo()->fCX) * 0.5f;

	return fDist <= fRadius;
}
