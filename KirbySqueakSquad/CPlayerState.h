#pragma once
#include "CStateManager.h"


class CPlayerState
{
	friend CStateManager;
private:

	PLAYERSTATE m_eState;

public:
	CPlayerState(PLAYERSTATE state);
	virtual ~CPlayerState();

	PLAYERSTATE GetState();

	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
};

class CPlayerMove : public CPlayerState
{

public:

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};