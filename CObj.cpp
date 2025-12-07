#include "pch.h"
#include "CObj.h"

CObj::CObj() : m_fSpeed(0.f), m_bDead(false), m_fAngle(0.f), m_fDistance(0.f),
	m_fDirX(0.f), m_fDirY(0.f)
{
	memset(&m_tInfo, 0, sizeof(INFO));
	memset(&m_tRect, 0, sizeof(RECT));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
