#include "pch.h"
#include "CMainGame.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CNormalMonster.h"
#include "CBossMonster.h"
#include "CAbstractFactory.h"
#include "CCollisionMgr.h"

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

	m_listObj[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::CreatePlayer());
	dynamic_cast<CPlayer*>(m_listObj[OBJ_PLAYER].front())->SetBullet(&m_listObj[OBJ_PLAYER_BULLET]);

	//CreateArrowMonster(3);

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
	
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_listObj[i].begin();
			iter != m_listObj[i].end();)
		{
			int iResult = (*iter)->Update();
			if (iResult == DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				iter++;
		}
	}
	CCollisionMgr::PlayerBulletCollide(m_listObj[OBJ_PLAYER_BULLET], m_listObj[OBJ_MONSTER]);
	CCollisionMgr::MonsterBulletCollide(m_listObj[OBJ_MONSTER_BULLET], m_listObj[OBJ_PLAYER]);
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto pObj : m_listObj[i])
		{
			pObj->Render(m_hDC);
		}
	}
}

void CMainGame::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto pObj : m_listObj[i])
		{
			Safe_Delete<CObj*>(pObj);
		}
	}

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
		dynamic_cast<CMonster*>(pNoramlMonster)->SetTarget(m_listObj[OBJ_PLAYER].front());
		m_listObj[OBJ_MONSTER].push_back(pNoramlMonster);
	}
	for (CObj* pMonster : m_listObj[OBJ_MONSTER])
	{
		dynamic_cast<CMonster*>(pMonster)->SetBullet(&m_listObj[OBJ_MONSTER_BULLET]);
	}
	dynamic_cast<CPlayer*>(m_listObj[OBJ_PLAYER].front())->SetTargetMonster(&m_listObj[OBJ_MONSTER]);
}

void CMainGame::CreateBossMonster()
{
	CObj* pBossMonster = CAbstractFactory<CBossMonster>::CreateMonster(WINCX >> 1, -100.f, 1000);
	dynamic_cast<CMonster*>(pBossMonster)->SetLimitLine(400.f);
	dynamic_cast<CMonster*>(pBossMonster)->SetTarget(m_listObj[OBJ_PLAYER].front());
	m_listObj[OBJ_MONSTER].push_back(pBossMonster);
	dynamic_cast<CMonster*>(pBossMonster)->SetBullet(&m_listObj[OBJ_MONSTER_BULLET]);
	dynamic_cast<CMonster*>(pBossMonster)->SetTarget(m_listObj[OBJ_PLAYER].front());

	dynamic_cast<CPlayer*>(m_listObj[OBJ_PLAYER].front())->SetTargetMonster(&m_listObj[OBJ_MONSTER]);
}
