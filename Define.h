#pragma once
#define		WINCX 800
#define		WINCY 600
#define		PURE  = 0
#define		NOEVENT 0
#define		DEAD 1
#define		PI 3.1415

//몬스터 상수
const float NORMAL_MONSTER_WAVE_COOLTIME = 4000;
const float BOSS_MONSTER_WAVE_COOLTIME = 1000000;
const DWORD NORMAL_MONSTER_SHOT_COOLTIME = 3000;
const DWORD BOSS_MONSTER_SCREW_SHOT_COOLTIME = 100;
const DWORD BOSS_MONSTER_SPREAD_SHOT_COOLTIME = 300;
const DWORD BOSS_MONSTER_SUNFLOWER_SHOT_COOLTIME = 3000;
const DWORD PLAYER_SHOT_COOLTIME = 100;

extern HWND g_hWnd;

enum eArmor
{
	NORMAL = 0, SPREAD, SCREW, LEADING, SUNFLOWER
};

enum eDir
{
	UP, DOWN
};

enum eObjID
{
	OBJ_PLAYER = 0, OBJ_MONSTER, OBJ_SHIELD, OBJ_ITEM,
	OBJ_MONSTER_BULLET, OBJ_PLAYER_BULLET, OBJ_END
};

typedef struct tagInfo
{
	float		fX, fY;
	float		fCX, fCY;

}INFO;

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}