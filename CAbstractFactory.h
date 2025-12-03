#include "pch.h"
#include "CObj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {};
	~CAbstractFactory() {};
public:
	static CObj* CreatePlayer()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetLife(10);
		return pObj;
	}
	//위치 세팅
	static CObj* Create(float fX, float fY)
	{
		CObj* pObj = new T();
		pObj->Initialize();
		pObj->SetPos(fX, fY);
		return pObj;
	}
	static CObj* CreateMonster(float fX, float fY, int iLife)
	{
		CObj* pObj = new T();
		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetLife(iLife);
		return pObj;
	}
};