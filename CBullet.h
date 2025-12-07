#pragma once
#include "CBulletAbstract.h"

class CBullet : public CBulletAbstract
{
public:
	CBullet();
	~CBullet();
public:
	void Initialize()	override;
	int	 Update()	override;
	void Render(HDC hDC)override;
	void Release()		override;
public:
	void ResolveCollision();
};