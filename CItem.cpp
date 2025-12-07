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
	m_fSpeed = 3.f;
}

int CItem::Update()
{
	if (m_bDead)
		return DEAD;
	
	m_tInfo.fY += m_fSpeed;

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

	MoveToEx(hDC, m_tInfo.fX - 5, m_tInfo.fY - 10, nullptr);
	LineTo(hDC, m_tInfo.fX + 5, m_tInfo.fY - 10);

	LineTo(hDC, m_tInfo.fX + 5, m_tInfo.fY - 4);

	LineTo(hDC, m_tInfo.fX, m_tInfo.fY);

	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX, m_tInfo.fY + 7);

	MoveToEx(hDC, (m_tInfo.fX), m_tInfo.fY + 9, nullptr);
	LineTo(hDC, m_tInfo.fX, m_tInfo.fY + 11);

}
