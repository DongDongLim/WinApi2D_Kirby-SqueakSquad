#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"



CPlayerIdle::CPlayerIdle()
{
}

CPlayerIdle::~CPlayerIdle()
{
}

void CPlayerIdle::update()
{

}

void CPlayerIdle::Enter()
{
	m_pPlayer->GetAnimator()->Play(L"Idle");
}

void CPlayerIdle::Exit(PLAYERSTATE state)
{
	CEventManager::getInst()->EventChangePlayerState(state);
}