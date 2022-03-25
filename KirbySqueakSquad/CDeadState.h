#pragma once
#include "CState.h"
class CDeadState : public CState
{
public:
	CDeadState(STATE_MON state);
	virtual ~CDeadState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();


};

