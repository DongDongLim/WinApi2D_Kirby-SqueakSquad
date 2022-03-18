#pragma once
class CPlayer;
class CState;
class CPlayerState;



class CStateManager
{
	SINGLETON(CStateManager);

private:

	CPlayer* m_pPlayer;
	map<PLAYERSTATE, CPlayerState*> m_mPlayerState;

	CPlayerState* m_pCurState;
	PLAYERSTATE m_eCurState;
	PLAYERSTATE m_ePrevState;
	COMMANDKEY m_eCurCommand;

	float m_fcommandTimer;

public:
	void SetPlayer(CPlayer* player);
	CPlayer* GetPlayer();

	void AddState(PLAYERSTATE state, CPlayerState* stateclass);
	void ChangeState(PLAYERSTATE state);

	void CommandSave();

	void update();

	COMMANDKEY GetCommend();

	CPlayerState* FindState(PLAYERSTATE state);
};

