#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CTile.h"
#include "CGravity.h"



void OnIdleCollison(DWORD_PTR state, CCollider* other)
{
	if (other->GetObj()->GetGroup() == GROUP_GAMEOBJ::TILE)
	{
		CTile* tile = (CTile*)other->GetObj();
		if (tile->GetGroup() == GROUP_TILE::GROUND)
		{
			CPlayerIdle* idle = (CPlayerIdle*)state;
			idle->AddGroundCollider((CCollider*)other);
		}
	}
}


CPlayerIdle::CPlayerIdle()
{
	m_eState = PLAYERSTATE::IDLE;
	//m_pPlayer->SetCollisonCallBack(OnIdleCollison, (DWORD_PTR)this);
	m_fWallLength = 0;
	m_pPlayerCollider = m_pPlayer->GetCollider();
	m_fGroundLength = (m_pPlayerCollider->GetScale() / 2).Length()
		+ (fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE) / 2).Length();
	m_bIsJump = false;
	for (int i = 0; i < 8; ++i)
	{
		m_pGroundCollider[i] = nullptr;
	}
}

CPlayerIdle::~CPlayerIdle()
{

}

void CPlayerIdle::GoundCheck()
{
	// 지금 오브젝트 기준으로 생각했는데 플레이어 기준으로 생각해보자
	for (int i = 0; i < 8; ++i)
	{
		float fRealTimeLength = fPoint(abs(m_pPlayerCollider->GetFinalPos().x
			- m_pGroundCollider[i]->GetFinalPos().x)
			, abs(m_pPlayerCollider->GetFinalPos().y
				- m_pGroundCollider[i]->GetFinalPos().y)).Length();
		if (m_fGroundLength > fRealTimeLength)
		{
			fPoint fLeftUpPos = fPoint(-1, -1).normalize();
			fPoint fRightDownPos = fPoint(1, 1).normalize();
			fPoint fPlayerDisPos = (m_pPlayerCollider->GetFinalPos() - m_pGroundCollider[i]->GetFinalPos()).normalize();;
			if (fPlayerDisPos.y < fLeftUpPos.y)
			{
				m_pPlayer->GetRigidBody()->
					SetMaxPositiveVelocity(fPoint(
						m_pPlayer->GetRigidBody()->
						GetMaxPositiveVelocity().x,
						0));
				m_pPlayer->SetPos(fPoint(m_pPlayer->GetPos().x
					, ((fPlayerDisPos * fRealTimeLength)
					+ m_pPlayerCollider->GetOffsetPos()).y));
			}
			if (fPlayerDisPos.y > fRightDownPos.y)
			{
				m_pPlayer->GetRigidBody()->
					SetMaxNegativeVelocity(fPoint(
						m_pPlayer->GetRigidBody()->
						GetMaxNegativeVelocity().x,
						0));
				m_pPlayer->SetPos(fPoint(m_pPlayer->GetPos().x
					, ((fPlayerDisPos * fRealTimeLength)
						+ m_pPlayerCollider->GetOffsetPos()).y));
			}
			if (fPlayerDisPos.x < fLeftUpPos.x)
			{
				m_pPlayer->GetRigidBody()->
					SetMaxNegativeVelocity(fPoint(
						0,
						m_pPlayer->GetRigidBody()->
						GetMaxNegativeVelocity().y));
				m_pPlayer->SetPos(fPoint(
					((fPlayerDisPos * fRealTimeLength)
						+ m_pPlayerCollider->GetOffsetPos()).x
					, m_pPlayer->GetPos().y));
			}
			if (fPlayerDisPos.x > fRightDownPos.x)
			{
				m_pPlayer->GetRigidBody()->
					SetMaxPositiveVelocity(fPoint(
						0,
						m_pPlayer->GetRigidBody()->
						GetMaxPositiveVelocity().y));
				m_pPlayer->SetPos(fPoint(
					((fPlayerDisPos * fRealTimeLength)
						+ m_pPlayerCollider->GetOffsetPos()).x
					, m_pPlayer->GetPos().y));
			}			
		}
		else
		{
			m_pGroundCollider[i] = nullptr;
		}
	}
}

void CPlayerIdle::AddGroundCollider(CCollider* ground)
{
	for(int i = 0; i < 8; ++i)
	{
		if (nullptr == m_pGroundCollider[i])
		{
			m_pGroundCollider[i] = ground;
			break;
		}
	}
}


void CPlayerIdle::KeyUpdate()
{
	if (Key(VK_LEFT))
	{
		if (0 != m_pPlayer->GetRigidBody()->GetMaxNegativeVelocity().x)
			Exit(PLAYERSTATE::MOVE);
	}
	if (Key(VK_RIGHT))
	{
		if (0 != m_pPlayer->GetRigidBody()->GetMaxPositiveVelocity().x)
			Exit(PLAYERSTATE::MOVE);
	}
	if (KeyDown('C'))
	{
		Exit(PLAYERSTATE::ATTACK);
	}
	if (KeyDown('X') || KeyDown('V'))
	{
		CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::JUMP);
		m_bIsJump = true;
	}
}

void CPlayerIdle::update()
{
	
	GoundCheck();

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