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

}

void CPlayerFly::Exit(PLAYERSTATE state)
{
	CEventManager::getInst()->EventLoadPlayerState(state);
}