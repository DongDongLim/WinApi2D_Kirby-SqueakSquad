#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayer.h"
#include "CGravity.h"


CPlayerFly::CPlayerFly()
{
	m_eState = PLAYERSTATE::FLY;
	m_fAnimSpeed = 0;
	m_fKeepTimer = m_fAnimSpeed;
}

CPlayerFly::~CPlayerFly()
{

}

void CPlayerFly::Anim()
{
	if (m_bIsActive)
	{
		if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() != m_pPlayer->GetAnimString().g_wUP)
		{
			if (Key(VK_UP) || Key('X') || Key('V') || KeyDown('X') || KeyDown('V'))
			{
				m_pPlayer->GetAnimator()->Play(m_pPlayer->GetAnimString().g_wUPMOVE);
				m_fKeepTimer = 0;
			}
			else
			{
				m_pPlayer->GetAnimator()->Play(m_pPlayer->GetAnimString().g_wUPIDLE);
			}
		}
		else
		{
			if (m_fKeepTimer <= 0)
			{
				m_fAnimSpeed = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
				m_pPlayer->GetAnimator()->Play(m_pPlayer->GetAnimString().g_wUPIDLE);
			}
		}
	}
}

void CPlayerFly::KeyUpdate()
{
	m_pPlayer->GetRigidBody()->SetVelocity(fPoint(m_pPlayer->GetRigidBody()->GetVelocity().x, 0.f));
	if (m_bIsActive)
	{
		if (Key(VK_UP) || Key('X') || Key('V') || KeyDown('X') || KeyDown('V'))
		{
			m_pPlayer->GetRigidBody()->SetVelocity(fPoint(m_pPlayer->GetRigidBody()->GetVelocity().x, -150.f));
		}
		if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() != m_pPlayer->GetAnimString().g_wUP)
		{
			m_fKeepTimer = m_fAnimSpeed;
		}
	}
	else
	{
		Exit(PLAYERSTATE::IDLE);
	}
}

void CPlayerFly::update()
{
	m_fKeepTimer -= fDT;
	if (m_fKeepTimer <= 0)
		KeyUpdate();
}

void CPlayerFly::Enter()
{
	m_bIsActive = true;
	m_pPlayer->GetAnimator()->Play(m_pPlayer->GetAnimString().g_wUP);
	m_fAnimSpeed = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
	m_fKeepTimer = m_fAnimSpeed;
}

void CPlayerFly::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	if (state != PLAYERSTATE::END)
		CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}