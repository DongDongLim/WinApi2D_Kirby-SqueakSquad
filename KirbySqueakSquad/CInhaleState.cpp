#include "framework.h"
#include "CInhaleState.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CAnimator.h"
#include "CGravity.h"

CInhaleState::CInhaleState(STATE_MON state)
	: CState(state)
{
}

CInhaleState::~CInhaleState()
{
}

void CInhaleState::update()
{
	if (nullptr == m_pPlayer)
		return;

	fPoint fptPlayerPos = m_pPlayer->GetPos();

	fPoint fptMonsterPos = m_pMonster->GetPos();
	
	if (nullptr != m_pMonster->GetTarget())
	{
		fptPlayerPos = m_pMonster->GetTarget()->GetPos();
	}

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();

	fPoint pos = m_pMonster->GetPos();
	pos += fvDiff.normalize() * 100 * fDT;
	m_pMonster->SetPos(pos);
	if (fLen < 8.f)
	{
		if (m_pPlayer->GetAttackType() == ATTACK_TYPE::THROW)
		{
			if(nullptr == m_pMonster->GetTarget())
				ChangeAIState(GetOwnerAI(), STATE_MON::DEAD);
		}
		else
		{
			ChangeAIState(GetOwnerAI(), STATE_MON::DEAD);
		}
	}
}

void CInhaleState::Enter()
{
	m_pMonster = GetMonster();
	m_pMonster->GetAnimator()->Play(m_pMonster->GetStringInfo().Damaged);
	m_pMonster->SetGroundCheck(false);
}

void CInhaleState::Exit()
{
}
