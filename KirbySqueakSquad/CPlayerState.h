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
	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit(PLAYERSTATE state) = 0;
};

class CPlayerIdle : public CPlayerState
{
private:
	float m_fDelayTime;
	float m_fKeepDelayTime;


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
	float m_fGravity;


public:
	CPlayerFall();
	~CPlayerFall();

	void SetTarget(COLLIONTARGET target);

	virtual void Anim();
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

// 상태 상속 안받고 그냥 돌려도 될듯? 컴퍼넌트로 해도 되겠다
// TODO : 추후 컴퍼넌트로 돌려서 애니메이션 있는 오브젝트가 모두 사용 가능하도록 변경
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