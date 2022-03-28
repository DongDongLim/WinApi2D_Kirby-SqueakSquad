#include "framework.h"
#include "CTraceState.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CRigidBody.h"

CTraceState::CTraceState(STATE_MON state)
	: CState(state)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	CPlayer* pPlayer = CStateManager::getInst()->GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();
	if (fLen >= pMonster->GetMonInfo().fRecogRange)
	{
		ChangeAIState(GetOwnerAI(), STATE_MON::IDLE);
	}

	fPoint pos = pMonster->GetPos();
	pos += fvDiff.normalize() * pMonster->GetSpeed() * fDT;
	pMonster->GetRigidBody()->AddVelocity(fPoint((fvDiff.normalize() * pMonster->GetSpeed()).x, 0));
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
