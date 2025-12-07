#pragma once
#include "CObj.h"

class CBulletAbstract : public CObj
{
public:
	CBulletAbstract();
	virtual ~CBulletAbstract();
public:
	virtual void Initialize()PURE;
	virtual int	 Update()PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()PURE;
public:
	eBulletInfo GetBulletInfo() {return m_eBulletInfo;}
protected:
	eBulletInfo m_eBulletInfo;
};