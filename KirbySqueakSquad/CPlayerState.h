#pragma once
#include "CStateManager.h"
class CPlayer;

class CPlayerState
{
protected:
	CPlayer* m_pPlayer;

public:
	CPlayerState();
	virtual ~CPlayerState();

	CPlayer* GetPlayer();

	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit(PLAYERSTATE) = 0;
};

class CPlayerIdle : public CPlayerState
{

public:
	CPlayerIdle();
	~CPlayerIdle();

	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};

class CPlayerMove : public CPlayerState
{
private:

public:
	CPlayerMove();
	~CPlayerMove();

	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};

class CPlayerJump : public CPlayerState
{

public:
	CPlayerJump();
	~CPlayerJump();

	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};

class CPlayerAttack : public CPlayerState
{

public:
	CPlayerAttack();
	~CPlayerAttack();

	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};

class CPlayerEat : public CPlayerState
{

public:
	CPlayerEat();
	~CPlayerEat();

	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};

class CPlayerFly : public CPlayerState
{

public:
	CPlayerFly();
	~CPlayerFly();

	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};