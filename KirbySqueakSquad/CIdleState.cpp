#include "framework.h"
#include "CIdleState.h"
#include "CPlayer.h"
#include "CMonster.h"

CIdleState::CIdleState(STATE_MON state)
	: CState(state)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	CPlayer* pPlayer = CStateManager::getInst()->GetPlayer();
	if (nullptr == pPlayer)
		return;
	CMonster* pMonster = GetMonster();
	if (pMonster->GetIsEaten())
		ChangeAIState(GetOwnerAI(), STATE_MON::TRACE);
	if(pMonster->isDead())
		ChangeAIState(GetOwnerAI(), STATE_MON::DEAD);
	//fPoint fptPlayerPos = pPlayer->GetPos();

	//CMonster* pMonster = GetMonster();
	//fPoint fptMonsterPos = pMonster->GetPos();

	//fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	//float fLen = fvDiff.Length();
	//if (fLen < pMonster->GetMonInfo().fRecogRange)
	//{
	//	//ChangeAIState(GetOwnerAI(), STATE_MON::TRACE);
	//}

}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}
