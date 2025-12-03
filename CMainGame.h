#pragma once
#include "Define.h"
#include "CObj.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void	Initialize();
	void	Update();
	void	Render();
	void	Release();
public:
	void CreateArrowMonster(int iCount);
private:
	HDC		m_hDC;
	CObj* m_pPlayer;
	list<list<CObj*>> m_listMonsterContainer;
	list<CObj*> m_listObj[OBJ_END];
	DWORD m_dwLastWaveTime;
};

