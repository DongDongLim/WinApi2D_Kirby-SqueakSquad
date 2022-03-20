#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"
#include "CCollider.h"



void OnCollisonExit(DWORD_PTR state, CCollider* other)
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
	m_pPlayer->SetCollisonExitCallBack(OnCollisonExit, (DWORD_PTR)this);
}

CPlayerIdle::~CPlayerIdle()
{
}


void CPlayerIdle::update()
{
	if (KeyDown(VK_LEFT) || KeyDown(VK_RIGHT))
	{
		Exit(PLAYERSTATE::MOVE);
	}
	if (KeyDown('C'))
	{
		Exit(PLAYERSTATE::ATTACK);
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
}

void CPlayerIdle::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState); 
}