#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"


CPlayerFly::CPlayerFly()
{

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
	CEventManager::getInst()->EventChangePlayerState(state);
}