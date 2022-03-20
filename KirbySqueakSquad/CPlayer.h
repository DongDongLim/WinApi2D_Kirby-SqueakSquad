#pragma once
#include "CGameObject.h"
#include "CStateManager.h"
#include "CRigidBody.h"


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
	const float m_fVelocity = 800.f;
	const float m_fMoveInertia = 0.2f;
	const float m_fVerticalSpeed = 100.f;
	const float m_fJumpTime = 1.f;
	const float m_fMaxSpeed = 100.f;

};

class CPlayer : public CGameObject
{
	friend CStateManager;
private:
	const float m_fMaxSpeed = 300.f;
	
	// 플레이어 애니메이션 재생을 위한 이미지들
	vector<CD2DImage*> m_pImg;
	// 플레이어 애니메이션 이미지의 키값
	vector<wstring> m_wImgKey;
	// 플레이어 애니메이션 동작의 키값
	vector<vector<wstring>*> m_wAnimKey;
	
	//const float m_fCommandTime = 0.2f;
	bool m_bIsRight;
	bool m_bIsGround;
	bool m_bIsWall[2];
	//int m_bIsGroundCount;
	void PlayerAttack(DWORD_PTR, DWORD_PTR);
	list<COLLIDER_FUNC> m_arrFunc;
	DWORD_PTR m_colliderState;
	list<COLLIDER_FUNC> m_arrEnterFunc;
	DWORD_PTR m_colliderEnterState;
	list<COLLIDER_FUNC> m_arrExitFunc;
	DWORD_PTR m_colliderExitState;

public:

	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();
	
	virtual void update();
	virtual void render();

	void SetIsGround(bool ground);
	void SetIsWall(bool wall, bool isright);

	bool GetDir();
	bool GetIsGround();
	bool* GetIsWall();

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

