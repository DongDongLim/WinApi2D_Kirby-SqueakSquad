#include "framework.h"
#include "CState.h"
#include "CPlayerState.h"


CStateManager::CStateManager()
{
	m_pPlayer = nullptr;
	m_mPlayerState = {};
	m_mCurPlayeState = {};
}

CStateManager::~CStateManager()
{
	map<PLAYERSTATE, CPlayerState*>::iterator iter = m_mPlayerState.begin();
	for (; iter != m_mPlayerState.end(); ++iter)
	{
		delete iter->second;
	}
}

void CStateManager::SetPlayer(CPlayer* player)
{
	// 플레이어는 오직 하나!
	if (nullptr != m_pPlayer)
		assert(nullptr);
	m_pPlayer = player;
}

CPlayer* CStateManager::GetPlayer()
{
	return m_pPlayer;
}

void CStateManager::AddState(PLAYERSTATE state, CPlayerState* stateclass)
{
	m_mPlayerState.insert(make_pair(state, stateclass));
}

void CStateManager::ExitState(PLAYERSTATE state)
{
	m_arrErase.push_back(state);
}

void CStateManager::LoadState(PLAYERSTATE state)
{
	CPlayerState* pState = FindState(state);
	assert(pState);
	if (nullptr == FindPlayeState(state))
		pState->Enter();
	m_mCurPlayeState.insert(make_pair(state, pState));
}


void CStateManager::update()
{
	/* 커비의 커맨드는 일정 시간내에 입력이 아니라 특정 동작 중에 키 입력으로 받고 있음
	if (m_fcommandTimer > 0)
	{
		m_fcommandTimer -= fDT;
		m_ePrevState = PLAYERSTATE::END;
		m_eCurCommand = COMMANDKEY::END;
	}
	*/
	map<PLAYERSTATE, CPlayerState*>::iterator iter = m_mCurPlayeState.begin();
	for (; iter != m_mCurPlayeState.end(); ++iter)
	{
		iter->second->update();
	}
	for (int i = 0; i < m_arrErase.size(); ++i)
	{
		if (nullptr != FindPlayeState(m_arrErase[i]))
		{
			m_mCurPlayeState.erase(m_arrErase[i]);
		}
	}
	m_arrErase.clear();
}

void CStateManager::render()
{
	map<PLAYERSTATE, CPlayerState*>::iterator iter = m_mCurPlayeState.begin();
	for (; iter != m_mCurPlayeState.end(); ++iter)
	{
		iter->second->render();
	}
}

void CStateManager::SetCommend(COMMANDKEY commend)
{
	m_eCurCommand = commend;
}

int CStateManager::GetCurPlaySize()
{
	return m_mCurPlayeState.size();
}

COMMANDKEY CStateManager::GetCommend()
{
	return m_eCurCommand;
}

/*
void CStateManager::CommandSave()
{
	m_ePrevState = m_eCurState;
	m_fcommandTimer = m_pPlayer->m_fCommandTime;
}
*/

CPlayerState* CStateManager::FindState(PLAYERSTATE state)
{
	map<PLAYERSTATE, CPlayerState*>::iterator iter = m_mPlayerState.find(state);
	if (m_mPlayerState.end() != iter)
		return iter->second;
	return nullptr;
}

CPlayerState* CStateManager::FindPlayeState(PLAYERSTATE state)
{
	map<PLAYERSTATE, CPlayerState*>::iterator iter = m_mCurPlayeState.find(state);
	if (m_mCurPlayeState.end() != iter)
		return iter->second;
	return nullptr;
}
