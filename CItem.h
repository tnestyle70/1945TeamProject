#pragma once
#include "CObj.h"
#include "Define.h"

class CItem : public CObj
{
public:
	CItem();
	~CItem();
public:
	void Initialize() override;
	int Update() override;
	void Release() override;
	void Render(HDC hDC) override;
public:
	void SetItemType(eArmor eItem) { m_eItemType = eItem; }
	eArmor& GetItemType() { return m_eItemType; }
private:
	eArmor m_eItemType;
};