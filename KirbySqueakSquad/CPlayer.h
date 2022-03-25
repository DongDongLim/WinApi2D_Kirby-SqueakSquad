#pragma once
#include "CGameObject.h"
#include "CStateManager.h"
#include "CRigidBody.h"
#include "CMonster.h"


/*
#define LEFTDEFINE Key(VK_LEFT)
#define RIGHTDEFINE Key(VK_RIGHT)
#define UPDEFINE Key(VK_UP)
#define DOWNDEFINE Key(VK_DOWN)
#define ACTTACKDEFINE Key('C')
#define TRANSFORMDEFINE Key('Z')
*/
#define JUMPDEFINE Key('V')||Key('X')
#define KEYEMPTYDEFINE !Key(VK_LEFT)&&!Key(VK_RIGHT)&&! Key(VK_UP)&&!Key(VK_DOWN)&&! Key('C')&&!JUMPDEFINE&&!Key('Z')
#define ANYKEYDOWN KeyDown(VK_LEFT)||KeyDown(VK_RIGHT)||KeyDown(VK_UP)||KeyDown(VK_DOWN)||KeyDown('C')||KeyDown('V')||KeyDown('X')||KeyDown('Z')

/* TODO :	어떤 키를 입력 받았었는지를 체크해야함
			이걸 상태로 체크를 한다?
			아래 오른쪽 공격은 어떤 상태로?
			커비의 콤보는 최대 3개까지의 키 입력을 받음
			키 상태를 만들까?
			처음에는 상태를 일정 시간 저장하고 그 상태에서 다른 키가 눌리면
			콤보가 적용되는 것을 생각했는데 일단 그거부터 적용해보자
			키를 입력 받는 순간 그 키를 알아서 저장하면 좋겠지만 
			상태의 enter exit를 사용해서 만들어보는 과정을 먼저 진행해보자
			근데 그러면 일일이 만들어야되는데...
			잠깐 왜 굳이 상태를 저장하는 걸 CState를 사용하려 했지? 그냥 만들면 되잖아
*/

// 함수포인터를 위한 타입정의
typedef void(*COLLIDER_FUNC) (DWORD_PTR, CCollider*);


class CState;
class CD2DImage;

struct PLAYERINFO
{
	const float g_fAccel = 2.f;
	// 속력
	const float m_fVelocity = 50.f;
	// 감속
	const float m_fMoveInertia = 0.f;
	// 세로 속도
	const float m_fVerticalSpeed = 100.f;

	const float m_fJumpTime = 1.f;


	bool g_bIsRight = false;
	bool g_bIsUp = false;
	bool g_bIsDown = false;
	bool g_bIsLeft = false;

};


enum class ATTACK_TYPE
{
	NORMAL,
	CUTTER,
	THROW,

	SIZE,
};



class CPlayer : public CGameObject
{
	friend class CStateManager;
private:
	PLAYERINFO info;
	ATTACK_TYPE m_eAttackType;
	MON_TYPE m_pEatingMon;
	// 플레이어 애니메이션 재생을 위한 이미지들
	vector<CD2DImage*> m_pImg;
	// 플레이어 애니메이션 이미지의 키값
	vector<wstring> m_wImgKey;
	// 플레이어 애니메이션 동작의 키값
	vector<vector<wstring>*> m_wAnimKey;
	
	//const float m_fCommandTime = 0.2f;
	bool m_bIsRight;
	list<COLLIDER_FUNC> m_arrFunc;
	DWORD_PTR m_colliderState;
	list<COLLIDER_FUNC> m_arrEnterFunc;
	DWORD_PTR m_colliderEnterState;
	list<COLLIDER_FUNC> m_arrExitFunc;
	DWORD_PTR m_colliderExitState;



	// 땅과의 거리체크
	float m_fGroundLength;
	// 벽과의 거리체크
	float m_fWallLength;

	//한번에 만나는 벽은 최대 8개임;
	CCollider* m_pGroundCollider[8];

public:

	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();
	
	virtual void update();
	virtual void render();
	void GroundCheckRender();

	ATTACK_TYPE GetAttackType();

	PLAYERINFO& GetPlaeyrInfo();


	CCollider* GetGround();
	void AddGroundCollider(CCollider* ground);
	void GroundCheck();

	void SetAttackType(ATTACK_TYPE type);
	void SetMonType(MON_TYPE type);
	void SetDir(bool dir);

	MON_TYPE GetMonType();
	bool GetDir();

	void SetCollisonCallBack(COLLIDER_FUNC pFunc, DWORD_PTR state);
	//void DeleteColliderCallBack(COLLIDER_FUNC pFunc);
	void SetCollisonEnterCallBack(COLLIDER_FUNC pFunc, DWORD_PTR state);
	//void DeleteColliderEnterCallBack(COLLIDER_FUNC pFunc);
	void SetCollisonExitCallBack(COLLIDER_FUNC pFunc, DWORD_PTR state);
	//void DeleteColliderExitCallBack(COLLIDER_FUNC pFunc);

	virtual void OnCollision(CCollider* Other);
	virtual void OnCollisionEnter(CCollider* Other);
	virtual void OnCollisionExit(CCollider* Other);

};

