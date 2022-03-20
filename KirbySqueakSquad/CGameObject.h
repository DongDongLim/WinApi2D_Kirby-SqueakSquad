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
	// 현재 속한 그룹
	GROUP_GAMEOBJ m_eCurGroup;

	// Component
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;
	CGravity* m_pGravity;
	CRigidBody* m_pRigid;

	
	bool m_bAlive;
	void SetDead();

public:
	CGameObject();
	CGameObject(const CGameObject& other);
	virtual ~CGameObject();
	virtual CGameObject* Clone() = 0;

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

	virtual void update() = 0;			// 반드시 상속받은 객체가 update를 구현하도록 순수가상함수로 선언
	virtual void finalupdate();			// 상속받는 클래스가 오버라이딩 할 수 없게 막는 final 키워드
	virtual void render();
	virtual void component_render();	// 컴포넌트들의 영역을 표시하기 위해


	CCollider* GetCollider();				// 충돌체 반환
	void CreateCollider();					// 충돌체 생성

	virtual void OnCollision(CCollider* _pOther) {}			// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther) {}		// 재정의용 탈충돌 가상함수

	CAnimator* GetAnimator();				// 애니메이터 반환
	void CreateAnimator();					// 애니메이터 생성

	CGravity* GetGravity();					// 중력 반환
	void CreateGravity();					// 중력 생성

	CRigidBody* GetRigidBody();				//리지드바디 반환
	void CreateRigidBody();					//리지드바디 생성

};

