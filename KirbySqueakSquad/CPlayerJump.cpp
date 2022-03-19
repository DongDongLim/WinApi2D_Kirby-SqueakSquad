#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"


CPlayerJump::CPlayerJump()
{
	m_eState = PLAYERSTATE::JUMP;
}

CPlayerJump::~CPlayerJump()
{

}

void CPlayerJump::update()
{

}

void CPlayerJump::Enter()
{

}

void CPlayerJump::Exit(PLAYERSTATE state)
{
	CEventManager::getInst()->EventLoadPlayerState(state);
}