#include "framework.h"
#include "CInhaleState.h"
#include "CPlayer.h"
#include "CMonster.h"

CInhaleState::CInhaleState(STATE_MON state)
	: CState(state)
{
}

CInhaleState::~CInhaleState()
{
}

void CInhaleState::update()
{
	CPlayer* pPlayer = CStateManager::getInst()->GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();

	fPoint pos = pMonster->GetPos();
	pos += fvDiff.normalize() * 100 * fDT;
	pMonster->SetPos(pos);
	if (fLen < 8.f)
	{
		pMonster->SetDead();
		ChangeAIState(GetOwnerAI(), STATE_MON::DEAD);
	}
}

void CInhaleState::Enter()
{
}

void CInhaleState::Exit()
{
}
