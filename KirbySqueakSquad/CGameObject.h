#pragma once

class CCollider;
class CAnimator;
class CGravity;
class CRigidBody;

class CGameObject
{
	friend class CEventManager;

private:

	float m_fAccel;

	wstring m_strName;
	fPoint m_fptPos;
	fPoint m_fptScale;
	// ���� ���� �׷�
	GROUP_GAMEOBJ m_eCurGroup;

	// Component
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;
	CGravity* m_pGravity;
	CRigidBody* m_pRigid;

	
	bool m_bAlive;

public:
	CGameObject();
	CGameObject(const CGameObject& other);
	virtual ~CGameObject();
	virtual CGameObject* Clone() = 0;


	void SetDead();
	void SetLive();
	void SetPos(fPoint pos);
	void SetScale(fPoint scale);
	void SetName(wstring name);
	void SetGroup(GROUP_GAMEOBJ group);

	fPoint GetPos();
	fPoint GetScale();
	virtual fPoint GetRightPos();
	virtual fPoint GetLeftPos();
	virtual fPoint GetUpPos();
	virtual fPoint GetDownPos();
	wstring GetName();
	GROUP_GAMEOBJ GetGroup();

	bool isDead();

	virtual void update() = 0;			// �ݵ�� ��ӹ��� ��ü�� update�� �����ϵ��� ���������Լ��� ����
	virtual void finalupdate();			// ��ӹ޴� Ŭ������ �������̵� �� �� ���� ���� final Ű����
	virtual void render();
	virtual void component_render();	// ������Ʈ���� ������ ǥ���ϱ� ����


	CCollider* GetCollider();				// �浹ü ��ȯ
	void CreateCollider();					// �浹ü ����

	virtual void OnCollision(CCollider* _pOther) {}			// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionExit(CCollider* _pOther) {}		// �����ǿ� Ż�浹 �����Լ�

	CAnimator* GetAnimator();				// �ִϸ����� ��ȯ
	void CreateAnimator();					// �ִϸ����� ����

	CGravity* GetGravity();					// �߷� ��ȯ
	void CreateGravity();					// �߷� ����

	CRigidBody* GetRigidBody();				//������ٵ� ��ȯ
	void CreateRigidBody();					//������ٵ� ����

};

