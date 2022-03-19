#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"


CPlayerFly::CPlayerFly()
{
	m_eState = PLAYERSTATE::FLY;
}

CPlayerFly::~CPlayerFly()
{

}

void CPlayerFly::update()
{

}

void CPlayerFly::Enter()
{
	m_bIsActive = true;
}

void CPlayerFly::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
}