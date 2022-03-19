#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"


CPlayerEat::CPlayerEat()
{
	m_eState = PLAYERSTATE::EAT;
}

CPlayerEat::~CPlayerEat()
{

}

void CPlayerEat::update()
{

}

void CPlayerEat::Enter()
{

}

void CPlayerEat::Exit(PLAYERSTATE state)
{
	CEventManager::getInst()->EventLoadPlayerState(state);
}