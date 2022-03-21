#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CTile.h"
#include "CGravity.h"



void OnIdleCollisonExit(DWORD_PTR state, CCollider* other)
{
	/*if (((CPlayerMove*)state)->GetIsActive())
	{
		CGameObject* pOtherObj = other->GetObj();
		if (pOtherObj->GetGroup() == GROUP_GAMEOBJ::TILE)
		{
			CStateManager::getInst()->ExitState(PLAYERSTATE::IDLE);
		}
	}*/
}

void OnIdleCollison(DWORD_PTR state, CCollider* other)
{
	/*
	CPlayerIdle* stateIdle = (CPlayerIdle*)state;
	if (stateIdle->GetIsActive())
	{
		CGameObject* pOtherObj = other->GetObj();
		if (pOtherObj->GetGroup() == GROUP_GAMEOBJ::TILE)
		{
			if (((CTile*)pOtherObj)->GetGroup() == GROUP_TILE::GROUND)
			{
				CPlayer* player = CStateManager::getInst()->GetPlayer();
				float playerX;
				float groundX;
				float playerY;
				float groundY;
				playerY = player->GetCollider()->GetDownPos().y;
				groundY = other->GetUpPos().y;
				if (player->GetDir())
				{
					playerX = player->GetCollider()->GetRightPos().x;
					groundX = other->GetLeftPos().x;
					if (1 >= abs(playerX - groundX) && 1 <= abs(playerY - groundY))
					{

					}
				}
				else
				{
					playerX = player->GetCollider()->GetLeftPos().x;
					groundX = other->GetRightPos().x;
					if (1 >= abs(playerX - groundX) && 1 <= abs(playerY - groundY))
					{
					}
				}
			}
		}
	}
	*/
}


CPlayerIdle::CPlayerIdle()
{
	m_eState = PLAYERSTATE::IDLE;
	m_pPlayer->SetCollisonExitCallBack(OnIdleCollisonExit, (DWORD_PTR)this);
	m_pPlayer->SetCollisonCallBack(OnIdleCollison, (DWORD_PTR)this);
	m_fDelayTime = 0.2f;
	m_fKeepDelayTime = m_fDelayTime;
}

CPlayerIdle::~CPlayerIdle()
{

}

void CPlayerIdle::KeyUpdate()
{
	if (Key(VK_LEFT))
	{
		if (!m_pPlayer->GetIsWall()[0] || m_pPlayer->GetIsWall()[1])
		{
			m_pPlayer->SetIsWall(false, false);
			Exit(PLAYERSTATE::MOVE);
		}
	}		
	if (Key(VK_RIGHT))
	{
		if (!m_pPlayer->GetIsWall()[0] || !m_pPlayer->GetIsWall()[1])
		{
			m_pPlayer->SetIsWall(false, false);
			Exit(PLAYERSTATE::MOVE);
		}
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

void CPlayerIdle::update()
{
	if (m_pPlayer->GetGravity()->GetIsGround())
	{
		if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::Fall))
		{
			CStateManager::getInst()->ExitState(PLAYERSTATE::Fall);
			//m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0, 0));
		}
		m_fDelayTime = m_fKeepDelayTime;
	}
	else
	{
		m_fDelayTime -= fDT;
		if (m_fDelayTime <= 0)
		{
			if (nullptr == CStateManager::getInst()->FindPlayeState(PLAYERSTATE::JUMP))
			{
				CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::Fall);
				m_fDelayTime = m_fKeepDelayTime;
			}
		}
	}


	KeyUpdate();
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
	//m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
	//CStateManager::getInst()->ExitState(m_eState); 
}