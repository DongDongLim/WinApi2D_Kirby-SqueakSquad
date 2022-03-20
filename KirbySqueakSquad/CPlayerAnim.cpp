#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayer.h"

CPlayerAnim::CPlayerAnim()
{
	for (int i = 0; i < (int)PLAYERSTATE::END; ++i)
	{
		m_arrState.push_back((PLAYERSTATE)i);
	}
	
}

CPlayerAnim::~CPlayerAnim()
{

}

void CPlayerAnim::update()
{
	CPlayerState* state = nullptr;
	for (int i = m_arrState.size() - 1; i >= 0; --i)
	{
		state = CStateManager::getInst()->FindPlayeState(m_arrState[i]);
		if (nullptr != state)
		{
			state->Anim();
			break;
		}
	}	
}

void CPlayerAnim::Enter()
{

}


void CPlayerAnim::Exit(PLAYERSTATE state)
{

}