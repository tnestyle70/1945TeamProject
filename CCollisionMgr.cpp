#include "pch.h"
#include "CPlayer.h"
#include "CItem.h"
#include "CShield.h"
#include "CBulletAbstract.h"
#include "CCollisionMgr.h"
#include "CCloneBossBullet.h"

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
				pPlayerBullet->SetDead();
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
					pPlayer->SetLife(50);
				}
				pMonsterBullet->SetDead();
			}
		}
	}
}

void CCollisionMgr::PlayerMonsterCollide(list<CObj*> Player, list<CObj*> Monster)
{
	RECT rc = {};
	for (auto& pPlayer : Player)
	{
		for (auto& pMonster : Monster)
		{
			if (IntersectRect(&rc, pPlayer->GetRect(), pMonster->GetRect()))
			{
				pPlayer->GetDamage();
			}
		}
	}
}

void CCollisionMgr::PlayerItemCollide(list<CObj*> Player, list<CObj*> Item)
{
	RECT rc = {};
	for (auto& pPlayer : Player)
	{
		for (auto& pItem : Item)
		{
			if (IntersectRect(&rc, pPlayer->GetRect(), pItem->GetRect()))
			{
				eArmor eItemType = dynamic_cast<CItem*>(pItem)->GetItemType();

				if (eItemType == eArmor::SHIELD)
				{
					dynamic_cast<CPlayer*>(pPlayer)->CreateShield();
					pItem->SetDead();
				}
				else if (eItemType == eArmor::ULTIMATE)
				{
					dynamic_cast<CPlayer*>(pPlayer)->CreateUltimate();
					pItem->SetDead();
				}
				else
				{
					dynamic_cast<CPlayer*>(pPlayer)->SetArmorState(eItemType);
					pItem->SetDead();
				}
			}
		}
	}
}

void CCollisionMgr::ShieldBulletCollide(list<CObj*> Shield, list<CObj*> MonsterBullet)
{
	RECT rc = {};
	for (auto& pShield : Shield)
	{
		for (auto& pBullet : MonsterBullet)
		{
			if (IntersectRect(&rc, pShield->GetRect(), pBullet->GetRect()))
			{
				eBulletInfo eBulletInfo = dynamic_cast<CBulletAbstract*>(pBullet)->GetBulletInfo();
				if (eBulletInfo == eBulletInfo::TARGET_BULLET)
				{
					dynamic_cast<CShield*>(pShield)->TryParry(360.f - dynamic_cast<CCloneBossBullet*>(pBullet)->GetOriginAngle());
				}
				else
				{
					dynamic_cast<CShield*>(pShield)->TryParry(pBullet->GetAngle());
				}
				pBullet->SetDead();
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
