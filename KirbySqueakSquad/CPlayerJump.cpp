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
	isTurn = false;
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
			pos -= fPoint(0, m_fJumpSpeed) * fDT;
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
			m_fTurnSpeed -= 2 * fDT;
			pos -= fPoint(0, m_fTurnSpeed * 4) * fDT;
			if (m_fTurnSpeed <= -m_fTurnKeepSpeed)
			{
				Exit(PLAYERSTATE::Fall);
			}
		}
	}
	m_pPlayer->SetPos(pos);
}

void CPlayerJump::Anim()
{
	m_pPlayer->GetAnimator()->SetReverce(!m_pPlayer->GetDir());
	if (!isTurn)
		m_pPlayer->GetAnimator()->Play(L"Jump");
	else
	{
		m_pPlayer->GetAnimator()->Play(L"Turn");
		if (m_fTurnKeepSpeed == 0)
		{
			m_fTurnSpeed = m_pPlayer->GetAnimator()->GetFrameSpeed() * m_pPlayer->GetAnimator()->GetAnimSize();
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
}

void CPlayerJump::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}