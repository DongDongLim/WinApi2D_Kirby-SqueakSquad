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
	m_bIsActive = true;
}

void CPlayerJump::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
}