#include "pch.h"
#include "CMainGame.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CNormalMonster.h"
#include "CSpreadMonster.h"
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

	CObj* pPlayer = CAbstractFactory<CPlayer>::Create();
	m_listObj[OBJ_PLAYER].push_back(pPlayer);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);

	eBossPhase = eBossPhase::READY;
	m_dwBossCoolTime = 0.f;
	m_dwBossAppearanceTime = 200.f;
}

void CMainGame::Update()
{
	//일정 시간 지나면 몬스터 웨이브 생성
	DWORD dwNow = GetTickCount64();
	
	if (dwNow - m_dwNoralLastWaveTime >= NORMAL_MONSTER_WAVE_COOLTIME)
	{
		int iRandSpawn = rand() % 2;
		switch (iRandSpawn)
		{
		case 0: CreateSpreadMonster(3); break;
		case 1: CreateNoramlMonster(3); break;
		default:
			break;
		}
		//CreateSpreadMonster(3);
		//마지막으로 총 쏜 시각 갱신
		m_dwNoralLastWaveTime = dwNow;
	}
	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER);
	switch (eBossPhase)
	{
	case READY:
		m_dwBossCoolTime = dwNow;
		eBossPhase = eBossPhase::APPEAR;
		break;
	case APPEAR:
		if (dynamic_cast<CPlayer*>(pPlayer)->GetScore() >= 10)
		{
			CreateBossMonster();
			eBossPhase = eBossPhase::ATTACK;
		}
		break;
	case ATTACK:
		break;
	default:
		break;
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

void CMainGame::CreateSpreadMonster(int iCount)
{
	//첫번째 웨이브 몬스터 생성, 서로 다른 레벨값을 줘서 몬스터 생성
	for (int i = 0; i < iCount; ++i)
	{
		float fRandX = (float)(rand() % WINCX);
		CObj* pSpreadMonster = CAbstractFactory<CSpreadMonster>::CreateMonster(fRandX, -100.f, 5);
		//LimitLine을 400 이하의 랜덤한 수로 설정해서 대입을 시킨다.
		float fLimitLine = (float)(rand() % 300 + 100);
		dynamic_cast<CMonster*>(pSpreadMonster)->SetLimitLine(fLimitLine);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSpreadMonster);
	}
}

void CMainGame::CreateBossMonster()
{
	CObj* pBossMonster = CAbstractFactory<CBossMonster>::CreateMonster(WINCX >> 1, -100.f, 500);
	dynamic_cast<CMonster*>(pBossMonster)->SetLimitLine(400.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBossMonster);
}
