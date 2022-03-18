#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"

CPlayerAttack::CPlayerAttack()
{

}

CPlayerAttack::~CPlayerAttack()
{

}

void CPlayerAttack::update()
{

}

void CPlayerAttack::Enter()
{

}

void CPlayerAttack::Exit(PLAYERSTATE state)
{
	CEventManager::getInst()->EventChangePlayerState(state);
}