#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"
#include "CCollider.h"



void OnIdleCollisonExit(DWORD_PTR state, CCollider* other)
{
	if (((CPlayerMove*)state)->GetIsActive())
	{
		CGameObject* pOtherObj = other->GetObj();
		if (pOtherObj->GetGroup() == GROUP_GAMEOBJ::TILE)
		{
			CStateManager::getInst()->ExitState(PLAYERSTATE::IDLE);
		}
	}
}


CPlayerIdle::CPlayerIdle()
{
	m_eState = PLAYERSTATE::IDLE;
	m_pPlayer->SetCollisonExitCallBack(OnIdleCollisonExit, (DWORD_PTR)this);
}

CPlayerIdle::~CPlayerIdle()
{
}


void CPlayerIdle::update()
{
	if (Key(VK_LEFT) || Key(VK_RIGHT))
	{
		Exit(PLAYERSTATE::MOVE);
	}
	if (KeyDown('C'))
	{
		Exit(PLAYERSTATE::ATTACK);
	}
	if (KeyDown('X') || KeyDown('V'))
	{
		CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::JUMP);
	}
}

void CPlayerIdle::Anim()
{
	m_pPlayer->GetAnimator()->SetReverce(!m_pPlayer->GetDir());
	m_pPlayer->GetAnimator()->Play(L"Idle");
}

void CPlayerIdle::Enter()
{
	m_bIsActive = true;
	m_limmitDir = 0;
}

void CPlayerIdle::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState); 
}