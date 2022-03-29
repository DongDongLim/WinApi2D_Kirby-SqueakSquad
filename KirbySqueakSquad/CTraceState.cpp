#include "framework.h"
#include "CTraceState.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CRigidBody.h"
#include "CAnimator.h"

CTraceState::CTraceState(STATE_MON state)
	: CState(state)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	if (nullptr == m_pPlayer)
		return;

	fPoint fptPlayerPos = m_pPlayer->GetPos();

	fPoint fptMonsterPos = m_pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();

	if (m_pMonster->GetIsEaten())
		ChangeAIState(GetOwnerAI(), STATE_MON::INHALE);
	if (fLen >= m_pMonster->GetMonInfo().fRecogRange)
	{
		ChangeAIState(GetOwnerAI(), STATE_MON::IDLE);
	}

	fPoint pos = m_pMonster->GetPos();
	pos += fvDiff.normalize() * m_pMonster->GetSpeed() * fDT;
	m_pMonster->GetRigidBody()->SetVelocity(fPoint((fvDiff.normalize() * m_pMonster->GetSpeed()).x, m_pMonster->GetRigidBody()->GetVelocity().y));
}

void CTraceState::Enter()
{
	m_pMonster = GetMonster();
	m_pMonster->GetAnimator()->Play(m_pMonster->GetStringInfo().Move);
}

void CTraceState::Exit()
{
}
