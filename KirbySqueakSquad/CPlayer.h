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
	const float g_fAccel = 1.5f;
	const float m_fVelocity = 100;
	const float m_fMoveInertia = 0.2f;

};

class CPlayer : public CGameObject
{
	friend CStateManager;
private:
	

	// �÷��̾� �ִϸ��̼� ����� ���� �̹�����
	vector<CD2DImage*> m_pImg;
	// �÷��̾� �ִϸ��̼� �̹����� Ű��
	vector<wstring> m_wImgKey;
	// �÷��̾� �ִϸ��̼� ������ Ű��
	vector<vector<wstring>*> m_wAnimKey;
	
	//const float m_fCommandTime = 0.2f;
	bool m_bIsRight;
	bool m_bIsStart;
	float m_fStartStay;
	int m_bIsGroundCount;
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
	
	void Enter();
	virtual void update();
	virtual void render();

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

