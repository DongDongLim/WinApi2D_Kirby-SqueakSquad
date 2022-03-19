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
	m_bIsActive = true;
}

void CPlayerEat::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
}