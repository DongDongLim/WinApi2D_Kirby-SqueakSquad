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
	map<PLAYERSTATE, CPlayerState*> m_mCurPlayeState;

	vector<PLAYERSTATE> m_arrErase;
	PLAYERSTATE m_ePrevState;
	COMMANDKEY m_eCurCommand;

	//float m_fcommandTimer;

public:
	void SetPlayer(CPlayer* player);
	CPlayer* GetPlayer();

	void AddState(PLAYERSTATE state, CPlayerState* stateclass);
	void ExitState(PLAYERSTATE state);
	void LoadState(PLAYERSTATE state);

	//void CommandSave();

	void update();
	void render();

	void SetCommend(COMMANDKEY commend);
	int GetCurPlaySize();

	COMMANDKEY GetCommend();

	CPlayerState* FindState(PLAYERSTATE state);
	CPlayerState* FindPlayeState(PLAYERSTATE state);
};

