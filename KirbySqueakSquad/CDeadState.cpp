#include "framework.h"
#include "CDeadState.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "AI.h"
#include "CAnimator.h"

CDeadState::CDeadState(STATE_MON state)
	: CState(state)
{
}

CDeadState::~CDeadState()
{
}

void CDeadState::update()
{
	if (nullptr == m_pPlayer)
		return;
	if ((m_pPlayer->GetPos().x < m_pMonster->GetRegenPosX() + 3.f) && (m_pPlayer->GetPos().x > m_pMonster->GetRegenPosX() - 3.f))
	{
		ChangeAIState(GetOwnerAI(), STATE_MON::IDLE);
	}
}

void CDeadState::Enter()
{
	m_pMonster = GetMonster();
	m_pMonster->SetDead();
}

void CDeadState::Exit()
{
	m_pMonster->SetLive();
	m_pMonster->SetIsEaten(false);
	m_pMonster->SetPos(GetOwnerAI()->GetStartPos());
}
