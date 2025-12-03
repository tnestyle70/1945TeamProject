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
    void CreateBullet();
private:
    list<CObj*>* m_pBulletList;
    void        Key_Input();
};

