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
	void CreateNoramlMonster(int iCount);
	void CreateSpreadMonster(int iCount);
	void CreateBossMonster();
private:
	HDC		m_hDC;
	CObj* m_pPlayer;
	list<list<CObj*>> m_listMonsterContainer;
	list<CObj*> m_listObj[OBJ_END];
	DWORD m_dwNoralLastWaveTime;
	DWORD m_dwBossCoolTime;
	DWORD m_dwBossAppearanceTime;
	eBossPhase eBossPhase;
};

