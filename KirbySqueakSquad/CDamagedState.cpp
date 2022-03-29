#include "framework.h"
#include "CDamagedState.h"

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
}

void CDamagedState::Exit()
{
}
