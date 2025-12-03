#include "pch.h"
#include "CMainGame.h"
#include "CPlayer.h"
#include "CMonster.h"
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

	CreateArrowMonster(3);
}	

void CMainGame::Update()
{
	//일정 시간 지나면 몬스터 웨이브 생성
	DWORD dwNow = GetTickCount64();
	
	if (dwNow - m_dwLastWaveTime >= MONSTER_WAVE_COOLTIME)
	{
		CreateArrowMonster(3);
		//마지막으로 총 쏜 시각 갱신
		m_dwLastWaveTime = dwNow;
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
	CCollisionMgr::PlayerBulletCollide(m_listObj[OBJ_MONSTER_BULLET], m_listObj[OBJ_PLAYER]);
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

void CMainGame::CreateArrowMonster(int iCount)
{
	//첫번째 웨이브 몬스터 생성, 서로 다른 레벨값을 줘서 몬스터 생성
	for (int i = 0; i < iCount; ++i)
	{
		// 0 1 0 이런 식으로 레벨값을 설정해서 중심 기준으로 화살 모양을 만든다.
		//int iLevel = (iCount - i / 2 > 0) ? i : iCount - i;
		if (i == 0)
		{
			m_listObj[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::
				CreateMonster(WINCX * 0.5f - 100.f, -100.f, 5));
		}
		else if (i == 1)
		{
			m_listObj[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::
				CreateMonster(WINCX * 0.5f, 0.f ,5));
		}
		else if (i == 2)
		{
			m_listObj[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::
				CreateMonster(WINCX * 0.5f + 100.f, -100.f, 5));
		}
	}
	for (CObj* pMonster : m_listObj[OBJ_MONSTER])
	{
		dynamic_cast<CMonster*>(pMonster)->SetBullet(&m_listObj[OBJ_MONSTER_BULLET]);
	}
	/*
	for (size_t i = 0; i < m_listObj[OBJ_MONSTER].size(); ++i)
	{
		for (CObj* pMonster : m_listObj[OBJ_MONSTER])
		{
			dynamic_cast<CMonster*>(pMonster)->SetBullet(&m_listObj[OBJ_MONSTER_BULLET]);
		}
	}
	*/
	/*
	for (int i = 0; i < iCount; ++i)
	{
		m_listMonsterContainer.push_back(m_listObj[OBJ_MONSTER]);
	}
	for (auto pMonsterList : m_listMonsterContainer)
	{
		for (auto pMonster : pMonsterList)
		{
			dynamic_cast<CMonster*>(pMonster)->SetBullet(&m_listObj[OBJ_MONSTER_BULLET]);
		}
	}
	*/
}
