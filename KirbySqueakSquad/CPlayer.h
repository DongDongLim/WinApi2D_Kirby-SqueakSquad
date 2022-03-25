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

/* TODO :	� Ű�� �Է� �޾Ҿ������� üũ�ؾ���
			�̰� ���·� üũ�� �Ѵ�?
			�Ʒ� ������ ������ � ���·�?
			Ŀ���� �޺��� �ִ� 3�������� Ű �Է��� ����
			Ű ���¸� �����?
			ó������ ���¸� ���� �ð� �����ϰ� �� ���¿��� �ٸ� Ű�� ������
			�޺��� ����Ǵ� ���� �����ߴµ� �ϴ� �װź��� �����غ���
			Ű�� �Է� �޴� ���� �� Ű�� �˾Ƽ� �����ϸ� �������� 
			������ enter exit�� ����ؼ� ������ ������ ���� �����غ���
			�ٵ� �׷��� ������ �����ߵǴµ�...
			��� �� ���� ���¸� �����ϴ� �� CState�� ����Ϸ� ����? �׳� ����� ���ݾ�
*/

// �Լ������͸� ���� Ÿ������
typedef void(*COLLIDER_FUNC) (DWORD_PTR, CCollider*);


class CState;
class CD2DImage;

struct PLAYERINFO
{
	const float g_fAccel = 2.f;
	// �ӷ�
	const float m_fVelocity = 50.f;
	// ����
	const float m_fMoveInertia = 0.f;
	// ���� �ӵ�
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


	SIZE,
};



class CPlayer : public CGameObject
{
	friend class CStateManager;
private:
	PLAYERINFO info;
	ATTACK_TYPE m_eAttackType;
	MON_TYPE m_pEatingMon;
	// �÷��̾� �ִϸ��̼� ����� ���� �̹�����
	vector<CD2DImage*> m_pImg;
	// �÷��̾� �ִϸ��̼� �̹����� Ű��
	vector<wstring> m_wImgKey;
	// �÷��̾� �ִϸ��̼� ������ Ű��
	vector<vector<wstring>*> m_wAnimKey;
	
	//const float m_fCommandTime = 0.2f;
	bool m_bIsRight;
	list<COLLIDER_FUNC> m_arrFunc;
	DWORD_PTR m_colliderState;
	list<COLLIDER_FUNC> m_arrEnterFunc;
	DWORD_PTR m_colliderEnterState;
	list<COLLIDER_FUNC> m_arrExitFunc;
	DWORD_PTR m_colliderExitState;



	// ������ �Ÿ�üũ
	float m_fGroundLength;
	// ������ �Ÿ�üũ
	float m_fWallLength;

	//�ѹ��� ������ ���� �ִ� 8����;
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

