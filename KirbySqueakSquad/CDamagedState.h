#pragma once
#include "CState.h"
class CDamagedState : public CState
{
public:
	CDamagedState(STATE_MON state);
	virtual ~CDamagedState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();

};

