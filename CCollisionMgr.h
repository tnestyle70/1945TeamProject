#pragma once
#include "CObj.h"

class CCollisionMgr
{
public:
	static void PlayerBulletCollide(list<CObj*> Dst, list<CObj*> Src);
	static void ShieldBulletCollide(list<CObj*> Shield, list<CObj*> MonsterBullet);
	static void MonsterBulletCollide(list<CObj*> Dst, list<CObj*> Src);
	static void PlayerMonsterCollide(list<CObj*> Player, list<CObj*> Monster);
	static void PlayerItemCollide(list<CObj*> Player, list<CObj*> Item);
	static void CircleCollide(list<CObj*> Dst, list<CObj*> Src);
	static bool CheckCircle(CObj* pDst, CObj* pSrc);
};