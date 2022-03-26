#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"


CPlayerJump::CPlayerJump()
{
	m_eState = PLAYERSTATE::JUMP;
	m_fJumpSpeed = m_eInfo.m_fVerticalSpeed;
	m_fTurnSpeed = 0;
	m_fTurnKeepSpeed = 0;
	isTurn = false;
	m_fMaXHeight = 0;
}

CPlayerJump::~CPlayerJump()
{

}

void CPlayerJump::Jump()
{
	fPoint pos = m_pPlayer->GetPos();
	if (!isTurn)
	{
		if (Key('X') || Key('V'))
		{
			if (m_fMaXHeight >= m_pPlayer->GetPos().y)
				isTurn = true;
			else
				m_pPlayer->GetRigidBody()->
				AddVelocity(fPoint(0.f, -m_fJumpSpeed));
			
		}
		if (KeyUp('X') || KeyUp('V'))
		{
			if (!Key('X') && !Key('V'))
			{
				isTurn = true;
			}
		}
	}
	if (isTurn)
	{
		if (0 != m_fTurnKeepSpeed)
		{
			m_fTurnSpeed -= fDT;
			//m_pPlayer->GetRigidBody()->AddForce(fPoint(0.f, m_eInfo.m_fVerticalSpeed));
			//pos -= fPoint(0, m_fTurnSpeed * 4) * fDT;
			if (m_fTurnSpeed <= -m_fTurnKeepSpeed)
			{
				Exit(PLAYERSTATE::Fall);
			}
		}
		if (KeyDown(VK_UP) || KeyDown('X') || KeyDown('V'))
		{
			Exit(PLAYERSTATE::FLY);
		}
	}
	m_pPlayer->SetPos(pos);
}

void CPlayerJump::Anim()
{
	if (!isTurn)
		m_pPlayer->GetAnimator()->Play(m_pPlayer->GetAnimString().g_wJUMP);
	else
	{
		m_pPlayer->GetAnimator()->Play(m_pPlayer->GetAnimString().g_wTURN);
		if (m_fTurnKeepSpeed == 0)
		{
			m_fTurnSpeed = m_pPlayer->GetAnimator()->GetFrameSpeed() * (m_pPlayer->GetAnimator()->GetAnimSize()-1);
			m_fTurnKeepSpeed = m_fTurnSpeed;
		}
	}
}



void CPlayerJump::update()
{
	Jump();
}



void CPlayerJump::Enter()
{
	m_bIsActive = true;
	m_fTurnSpeed = 0;
	m_fTurnKeepSpeed = 0;
	isTurn = false;
	m_fMaXHeight = m_pPlayer->GetPos().y - 40.f;
}

void CPlayerJump::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	if (state != PLAYERSTATE::END)
		CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}