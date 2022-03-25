#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"


CPlayerEat::CPlayerEat()
{
	m_eState = PLAYERSTATE::EAT;
	nomalanimtime = 0;
	nomalanimKeeptime = nomalanimtime;
}

CPlayerEat::~CPlayerEat()
{

}

void CPlayerEat::Anim()
{
	if (KeyDown(VK_DOWN))
	{
		m_pPlayer->GetAnimator()->Play(L"Eat");
		nomalanimtime = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
		nomalanimKeeptime = nomalanimtime;
	}
}

void CPlayerEat::update()
{
	if (0 != nomalanimKeeptime)
	{
		nomalanimtime -= fDT;
		if (nomalanimtime <= 0)
		{
			m_pPlayer->SetAttackType((ATTACK_TYPE)m_pPlayer->GetMonType());
			Exit(PLAYERSTATE::IDLE);
		}
	}
	if (KeyDown('C'))
	{
		CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::ATTACK);
	}
}



void CPlayerEat::Enter()
{
	m_bIsActive = true;
	m_pPlayer->GetAnimator()->Play(L"Eating");
	nomalanimtime = 0;
	nomalanimKeeptime = nomalanimtime;
	if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::ATTACK))
		CStateManager::getInst()->FindPlayeState(PLAYERSTATE::ATTACK)->Exit(PLAYERSTATE::IDLE);
}

void CPlayerEat::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	if (state != PLAYERSTATE::END)
		CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}