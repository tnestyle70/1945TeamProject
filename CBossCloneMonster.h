#pragma once
#include "CMonster.h"

enum class eClonePattern
{
    ORBIT_AND_STRIKE, LINE_STRIKE, RANDOM_STRIKE
};

enum class eCloneState
{
    APPEAR, AIM, SHOT, VANISH
};

class CBossCloneMonster :
    public CMonster
{
public:
    CBossCloneMonster();
    ~CBossCloneMonster();
public:
    void Initialize() override;
    int  Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
    void DropItem()override {};
public:
    void CreateBullet();
    void UpdatePhase();
    void UpdateOrbitAndAttack();
    void UpdateLineStrike();
    void UpdateRandomStrike();
    void UpdateOrbitMove();
    void SetPattern(eClonePattern ePattern) { m_ePattern = ePattern; }
    void SetOrbitOffset(float fOffset) { m_fOrbitOffset = fOffset; }
    void SetOrbitSpawnDuration(float fOrbitAppearDuration) { m_fOrbitAppearDuration = fOrbitAppearDuration; }
    void SetLineOffset(float fOffset) { m_fLineOffset = fOffset; }
    void SetLineSpawnDuration(float fLineSpawnDuration) { m_fLineSpawnDuration = fLineSpawnDuration; }
private:
    eCloneState m_eState;
    DWORD m_dwAppearanceTime;
    //랜덤 스폰 패턴
    float m_fRandomAppearDuration;
    float m_fAimDuration;
    float m_fVanishDuration;
    bool m_bShot;
    eClonePattern m_ePattern;
    //원형 스폰 패턴
    float m_fCenterX;
    float m_fCenterY;
    bool m_bStart;
    float m_fOrbitAppearDuration;
    float m_fOrbitVanishDuration;
    float m_fSpawnAppearDuration;
    float m_fOrbitOffset;
    float m_fOrbitDistance;
    float m_fOrbitSpeed;
    float m_fOrbitAngle;
    //일렬 패턴 
    float m_fLineOffset;
    float m_fLineSpawnDuration;
    float m_fOffset;
};

