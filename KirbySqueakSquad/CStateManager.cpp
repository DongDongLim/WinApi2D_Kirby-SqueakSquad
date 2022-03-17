#include "framework.h"
#include "CStateManager.h"
#include "CState.h"


CStateManager::CStateManager()
{
	m_mPlayerState = {};
	m_ePlayerState = PLAYERSTATE::IDLE;
}

CStateManager::~CStateManager()
{
	map<PLAYERSTATE, CState*>::iterator iter = m_mPlayerState.begin();
	for (; iter != m_mPlayerState.end(); ++iter)
	{
		delete iter->second;
	}
}

void CStateManager::AddState(PLAYERSTATE state, CState* stateclass)
{
	m_mPlayerState.insert(make_pair(state, stateclass));
}

void CStateManager::ChangeState(PLAYERSTATE state, CState*& curstate)
{
	CState* pState = FindState(state);
	if (nullptr != pState)
	{
		if (nullptr != curstate)//현재 상태
			curstate->Exit();
		pState->Enter();
		curstate = pState;
	}

}

CState* CStateManager::FindState(PLAYERSTATE state)
{
	map<PLAYERSTATE, CState*>::iterator iter = m_mPlayerState.find(state);
	if (m_mPlayerState.end() != iter)
		return iter->second;
	return nullptr;
}
