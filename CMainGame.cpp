#include "pch.h"
#include "CMainGame.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CNormalMonster.h"
#include "CBossMonster.h"
#include "CAbstractFactory.h"
#include "CCollisionMgr.h"
#include "CObjMgr.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CObj* pPlayer = CAbstractFactory<CPlayer>::CreatePlayer();
	m_listObj[OBJ_PLAYER].push_back(pPlayer);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);

	m_dwBossLastWaveTime = 5000.f;
}	

void CMainGame::Update()
{
	//일정 시간 지나면 몬스터 웨이브 생성
	DWORD dwNow = GetTickCount64();
	
	if (dwNow - m_dwNoralLastWaveTime >= NORMAL_MONSTER_WAVE_COOLTIME)
	{
		CreateNoramlMonster(3);
		//마지막으로 총 쏜 시각 갱신
		m_dwNoralLastWaveTime = dwNow;
	}
	if (dwNow - m_dwBossLastWaveTime >= BOSS_MONSTER_WAVE_COOLTIME)
	{
		CreateBossMonster();
		m_dwBossLastWaveTime = dwNow;
	}

	CObjMgr::Get_Instance()->Update();
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	CObjMgr::Get_Instance()->Render(m_hDC);
}

void CMainGame::Release()
{
	CObjMgr::Get_Instance()->Release();
	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::CreateNoramlMonster(int iCount)
{
	//첫번째 웨이브 몬스터 생성, 서로 다른 레벨값을 줘서 몬스터 생성
	for (int i = 0; i < iCount; ++i)
	{
		float fRandX = (float)(rand() % WINCX);
		CObj* pNoramlMonster = CAbstractFactory<CNormalMonster>::CreateMonster(fRandX, -100.f, 5);
		//LimitLine을 400 이하의 랜덤한 수로 설정해서 대입을 시킨다.
		float fLimitLine = (float)(rand() % 300 + 100);
		dynamic_cast<CMonster*>(pNoramlMonster)->SetLimitLine(fLimitLine);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pNoramlMonster);
	}
}

void CMainGame::CreateBossMonster()
{
	CObj* pBossMonster = CAbstractFactory<CBossMonster>::CreateMonster(WINCX >> 1, -100.f, 1000);
	dynamic_cast<CMonster*>(pBossMonster)->SetLimitLine(400.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBossMonster);
}
