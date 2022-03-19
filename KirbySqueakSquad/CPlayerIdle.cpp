#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"



CPlayerIdle::CPlayerIdle()
{
	m_eState = PLAYERSTATE::IDLE;
}

CPlayerIdle::~CPlayerIdle()
{
}

void CPlayerIdle::update()
{
	m_pPlayer->GetAnimator()->SetReverce(!m_pPlayer->GetDir());
	if (KeyDown(VK_LEFT) || KeyDown(VK_RIGHT))
	{
		Exit(PLAYERSTATE::MOVE);
	}
	if (KeyDown('C'))
	{
		Exit(PLAYERSTATE::ATTACK);
	}
}

void CPlayerIdle::Enter()
{
	m_pPlayer->GetAnimator()->Play(L"Idle");
}

void CPlayerIdle::Exit(PLAYERSTATE state)
{
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}