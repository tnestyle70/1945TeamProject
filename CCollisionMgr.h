#pragma once
#include "CObj.h"

class CCollisionMgr
{
public:
	static void PlayerBulletCollide(list<CObj*> Dst, list<CObj*> Src);
	static void MonsterBulletCollide(list<CObj*> Dst, list<CObj*> Src);
	static void PlayerItemCollide(list<CObj*> Player, list<CObj*> Item);
	static void CircleCollide(list<CObj*> Dst, list<CObj*> Src);
	static bool CheckCircle(CObj* pDst, CObj* pSrc);
};