#include "framework.h"
#include "CDeadState.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "AI.h"

CDeadState::CDeadState(STATE_MON state)
	: CState(state)
{
}

CDeadState::~CDeadState()
{
}

void CDeadState::update()
{
	CPlayer* pPlayer = CStateManager::getInst()->GetPlayer();
	if (nullptr == pPlayer)
		return;
	CMonster* pMonster = GetMonster();
	if ((pPlayer->GetPos().x < pMonster->GetRegenPosX() + 3.f) && (pPlayer->GetPos().x > pMonster->GetRegenPosX() - 3.f))
	{
		ChangeAIState(GetOwnerAI(), STATE_MON::IDLE);
	}
}

void CDeadState::Enter()
{
}

void CDeadState::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->SetLive();
	pMonster->SetIsEaten(false);
	pMonster->SetPos(GetOwnerAI()->GetStartPos());
}
