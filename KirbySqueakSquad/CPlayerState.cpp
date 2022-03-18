#include "framework.h"
#include "CPlayerState.h"
#include "framework.h"
#include "CPlayerState.h"


CPlayerState::CPlayerState(PLAYERSTATE state)
{
	m_eState = state;
}

CPlayerState::~CPlayerState()
{
}

PLAYERSTATE CPlayerState::GetState()
{
	return m_eState;
}
