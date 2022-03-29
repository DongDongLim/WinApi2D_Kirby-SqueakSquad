#include "framework.h"
#include "CDamagedState.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CMonster.h"


CDamagedState::CDamagedState(STATE_MON state)
	: CState(state)
{
}

CDamagedState::~CDamagedState()
{
}

void CDamagedState::update()
{

}

void CDamagedState::Enter()
{
	m_pMonster = GetMonster();
	m_pMonster->GetAnimator()->Play(m_pMonster->GetStringInfo().Damaged);
}

void CDamagedState::Exit()
{
}
