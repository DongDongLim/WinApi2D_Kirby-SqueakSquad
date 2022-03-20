#pragma once

class CGameObject;

class CRigidBody
{
	friend class CGameObject;
private:
	CGameObject* m_pOwner;	// 주인
	fPoint m_fForce;		// 방향에 적용되는 힘
	fPoint m_fAccel;		// 가속도
	fPoint m_fVelocity;		// 속도
	fPoint m_fGAccel;		// 중력가속도
	float m_fMass;			// 질량
	float m_fFricCoeff;		// 마찰력
	float m_fMaxSpeed;		// 최대 속력

public:
	CRigidBody();
	CRigidBody(const CRigidBody& other);
	~CRigidBody();

	void AddForce(fPoint force);
	void SetMass(float mass);
	float GetMass();
		
	void SetVelocity(fPoint velocity);
	void AddVelocity(fPoint velocity);
	void SetMaxSpeed(float maxSpeed);
	void SetFricCoeff(float fricCoeff);
	void SetGAccel(fPoint gAceel);

	fPoint GetVelocity();

	void finalupdate();

private:
	void Move();

};