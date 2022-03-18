#pragma once
#include "CStateManager.h"
class CPlayer;

class CPlayerState
{
	CPlayer* m_pPlayer;
private:

public:
	CPlayerState();
	virtual ~CPlayerState();

	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
};

class CPlayerIdle : public CPlayerState
{

public:
	CPlayerIdle();
	~CPlayerIdle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class CPlayerMove : public CPlayerState
{

public:
	CPlayerMove();
	~CPlayerMove();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class CPlayerJump : public CPlayerState
{

public:
	CPlayerJump();
	~CPlayerJump();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class CPlayerAttack : public CPlayerState
{

public:
	CPlayerAttack();
	~CPlayerAttack();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class CPlayerEat : public CPlayerState
{

public:
	CPlayerEat();
	~CPlayerEat();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class CPlayerFly : public CPlayerState
{

public:
	CPlayerFly();
	~CPlayerFly();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};