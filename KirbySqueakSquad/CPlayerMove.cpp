#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"

CPlayerMove::CPlayerMove()
{
	
}

CPlayerMove::~CPlayerMove()
{

}

void CPlayerMove::update()
{
	PLAYERINFO m_eInfo;
	fPoint pos = m_pPlayer->GetPos();
	int dir = m_pPlayer->GetDir() ? 1 : -1;
	m_pPlayer->GetAnimator()->SetReverce(m_pPlayer->GetDir());
	if (CStateManager::getInst()->GetCommend() != COMMANDKEY::DASH)
	{
		m_pPlayer->GetAnimator()->Play(L"Move");
		pos.x += dir * m_eInfo.m_fVelocity * fDT;
	}
	else
	{
		m_pPlayer->GetAnimator()->Play(L"Dash");
		pos.x += dir * m_eInfo.m_fVelocity * m_eInfo.g_fAccel * fDT;
	}
	/*
	if (!m_bIsAnimStay)
	{
		if (CStateManager::getInst()->GetCommend() != COMMANDKEY::DASH)
		{
			m_pPlayer->GetAnimator()->Play(L"Move");
			pos.x += dir * m_eInfo.m_fVelocity * fDT;
		}
		else
		{
			m_pPlayer->GetAnimator()->Play(L"Dash");
			pos.x += dir * m_eInfo.m_fVelocity * m_eInfo.g_fAccel * fDT;
		}
	}
	else
	{
		GetAnimator()->Play(L"QuickStop");
		pos.x += dir * m_fVelocity * m_animStayTime * fDT;
		m_animStayTime -= fDT;
		if (m_animStayTime <= 0)
		{
			m_animStayTime = 0;
			m_bIsAnimStay = false;
		}
	}
	*/
	m_pPlayer->SetPos(pos);
}

void CPlayerMove::Enter()
{

}

void CPlayerMove::Exit(PLAYERSTATE state)
{
	CEventManager::getInst()->EventChangePlayerState(state);
}