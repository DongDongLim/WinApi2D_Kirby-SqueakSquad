#include "framework.h"
#include "CIdleState.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CMonster.h"
#include "CGravity.h"

CIdleState::CIdleState(STATE_MON state)
	: CState(state)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	if (nullptr == m_pPlayer)
		return;
	if (m_pMonster->GetIsEaten())
		ChangeAIState(GetOwnerAI(), STATE_MON::INHALE);
	if(m_pMonster->isDead())
		ChangeAIState(GetOwnerAI(), STATE_MON::DEAD);
	fPoint fptPlayerPos = m_pPlayer->GetPos();

	fPoint fptMonsterPos = m_pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();
	if (fLen < m_pMonster->GetMonInfo().fRecogRange)
	{
		ChangeAIState(GetOwnerAI(), STATE_MON::TRACE);
	}

}

void CIdleState::Enter()
{
	m_pMonster = GetMonster();
	m_pMonster->GetAnimator()->Play(m_pMonster->GetStringInfo().Idle);
	m_pMonster->SetGroundCheck(true);
}

void CIdleState::Exit()
{
}
