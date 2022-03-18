#pragma once

class CState;

enum class PLAYERSTATE
{
	IDLE,
	MOVE,
	DOWN,
	FLY,
	EAT,
	ATTACK,
	TRANSFORM,
	RIGHT,
	LEFT,

	END,
};

enum class COMMANDKEY
{
	DASH,

	END
};


class CStateManager
{
	SINGLETON(CStateManager);

private:

	map<PLAYERSTATE, CState*> m_mPlayerState;
	PLAYERSTATE m_eCurState;

public:
	void AddState(PLAYERSTATE state, CState* stateclass);
	void ChangeState(PLAYERSTATE state, PLAYERSTATE& curstate);

	CState* FindState(PLAYERSTATE state);
};

