#pragma once
#include "CObj.h"

class CPlayer :
    public CObj
{
public:
    CPlayer();
    virtual ~CPlayer();

public:
    void Initialize() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
    void SetBullet(list<CObj*>* pBullet) { m_pBulletList = pBullet; }
    void SetArmorState(eArmor eArmor) { m_eArmor = eArmor;}
    void CreateNoramlBullet();
    void CreateSunFlowerBullet();
    void CreateScrewBullet();
    void CreateSpreadBullet();
    void CreateLeadingBullet();
    void CreateShield();
private:
    list<CObj*>* m_pBulletList;
    void   Key_Input();
    eArmor m_eArmor;
};

