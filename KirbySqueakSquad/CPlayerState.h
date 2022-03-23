#pragma once
#include "CStateManager.h"
#include "CPlayer.h"

class CColider;

class CPlayerState
{
protected:
	PLAYERINFO m_eInfo;
	CPlayer* m_pPlayer;
	PLAYERSTATE m_eState;
	bool m_bIsActive;

public:
	CPlayerState();
	virtual ~CPlayerState();

	CPlayer* GetPlayer();
	bool GetIsActive();


	virtual void Anim() {}
	virtual void render() {}
	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit(PLAYERSTATE state) = 0;
};

class CPlayerIdle : public CPlayerState
{
private:
	CCollider* m_pPlayerCollider;

public:
	CPlayerIdle();
	~CPlayerIdle();

	void KeyUpdate();
	virtual void Anim();
	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};

class CPlayerMove : public CPlayerState
{
private:
	enum class COMMANDMOVE
	{
		NONE,
		DASH,
		CHANGEDIR,
		TURNOFF,
		IMPACT,

		END
	};
		
	COMMANDMOVE m_eCurCommand;
	COMMANDMOVE m_ePrevCommand;
	float m_fAnimStayTime;
	bool m_bIsDash;
	bool m_bIsStop;
	bool m_bStartDir;
	bool m_bIsDirChange;
	int m_dir;

	
public:
	CPlayerMove();
	~CPlayerMove();

	void Move();
	void Anim();
	
	void KeyUpdate();
	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};

class CPlayerJump : public CPlayerState
{
private:
	bool isTurn;
	float m_fJumpSpeed;
	float m_fTurnSpeed;
	float m_fTurnKeepSpeed;
	float m_fMaXHeight;

public:
	CPlayerJump();
	~CPlayerJump();

	void Jump();
	void Anim();

	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};

class CPlayerFall : public CPlayerState
{
public:
	enum class COLLIONTARGET
	{
		GROUND,
		MON,


		END,
	};

private:

	COLLIONTARGET m_eTarget;


public:
	CPlayerFall();
	~CPlayerFall();

	void SetTarget(COLLIONTARGET target);

	void KeyUpdate();
	virtual void Anim();
	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};


class CAttackObj;

class CPlayerAttack : public CPlayerState
{
private:
	float nomalanimtime;
	float nomalanimKeeptime;

	fPoint m_fAttRange;

	CAttackObj* m_pAttackobj;

public:
	CPlayerAttack();
	~CPlayerAttack();


	virtual void Anim();
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
private:
	float m_fAnimSpeed;
	float m_fKeepTimer;

public:
	CPlayerFly();
	~CPlayerFly();

	void Anim();

	void KeyUpdate();
	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};

// ���� ��� �ȹް� �׳� ������ �ɵ�? ���۳�Ʈ�� �ص� �ǰڴ�
// TODO : ���� ���۳�Ʈ�� ������ �ִϸ��̼� �ִ� ������Ʈ�� ��� ��� �����ϵ��� ����
class CPlayerAnim : public CPlayerState
{
private:
	vector<PLAYERSTATE> m_arrState;

public:
	CPlayerAnim();
	~CPlayerAnim();

	virtual void update();
	virtual void Enter();
	virtual void Exit(PLAYERSTATE state);
};