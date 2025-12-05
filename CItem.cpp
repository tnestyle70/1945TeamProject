#include "pch.h"
#include "CItem.h"
#include "CObjMgr.h"

CItem::CItem()
{
	ZeroMemory(&m_eItemType, sizeof(m_eItemType));
}

CItem::~CItem()
{
}

void CItem::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
}

int CItem::Update()
{
	if (m_bDead)
		return DEAD;
	
	__super::Update_Rect();

	return NOEVENT;
}

void CItem::Release()
{
}

void CItem::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}
