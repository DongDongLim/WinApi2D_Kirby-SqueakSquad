#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CTile.h"
#include "CGravity.h"


CPlayerIdle::CPlayerIdle()
{
	m_eState = PLAYERSTATE::IDLE;
	m_pPlayerCollider = m_pPlayer->GetCollider();
}

CPlayerIdle::~CPlayerIdle()
{

}


void CPlayerIdle::KeyUpdate()
{
	if (KeyDown('C'))
	{
		if (nullptr == CStateManager::getInst()->FindPlayeState(PLAYERSTATE::FLY))
		{
			Exit(PLAYERSTATE::ATTACK);
		}
	}
	else
	{
		if (Key(VK_UP))
		{
			if (m_pPlayer->GetGravity()->GetIsGround())
			{
				CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::FLY);
			}
		}
		if (Key(VK_LEFT))
		{
			if (!m_pPlayer->GetPlaeyrInfo().g_bIsLeft)
				CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::MOVE);
		}
		if (Key(VK_RIGHT))
		{
			if (!m_pPlayer->GetPlaeyrInfo().g_bIsRight)
				CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::MOVE);
		}
		if (KeyDown('X') || KeyDown('V'))
		{
			if (m_pPlayer->GetGravity()->GetIsGround())
			{
				if (nullptr == CStateManager::getInst()->FindPlayeState(PLAYERSTATE::FLY))
				{
					CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::JUMP);
				}
			}
		}
	}
}

void CPlayerIdle::update()
{
	if (m_pPlayer->GetGravity()->GetIsGround())
	{
		if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::Fall))
		{
			CStateManager::getInst()->ExitState(PLAYERSTATE::Fall);
		}
	}
	else
	{
		if (nullptr == CStateManager::getInst()->FindPlayeState(PLAYERSTATE::JUMP))
		{
			CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::Fall);
		}
	}


	KeyUpdate();
}



void CPlayerIdle::Anim()
{
	m_pPlayer->GetAnimator()->Play(L"Idle");
}



void CPlayerIdle::Enter()
{
	m_bIsActive = true;
}

void CPlayerIdle::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}