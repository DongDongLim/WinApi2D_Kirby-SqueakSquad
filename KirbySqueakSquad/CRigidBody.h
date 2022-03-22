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
	fPoint m_fPrevVelocity;		// 속도
	fPoint m_fGAccel;		// 중력가속도
	fPoint m_fPositiveMaxVelocity;	// 양의 최대 속력
	fPoint m_fNegativeMaxVelocity;	// 음의 최대 속력
	float m_fMass;			// 질량
	float m_fFricCoeff;		// 마찰력
	float m_fDelayTime;		// 업데이트 딜레이

public:
	CRigidBody();
	CRigidBody(const CRigidBody& other);
	~CRigidBody();

	void AddForce(fPoint force);
	void SetMass(float mass);
	float GetMass();
		
	void SetVelocity(fPoint velocity);
	void AddVelocity(fPoint velocity);
	void SetMaxPositiveVelocity(fPoint maxVelocity);
	void SetMaxNegativeVelocity(fPoint maxVelocity);
	void SetFricCoeff(float fricCoeff);
	void SetGAccel(fPoint gAceel);

	void RecoveryMaxPositiveVelocity();
	void RecoveryMaxNegativeVelocity();

	fPoint GetVelocity();
	fPoint GetMaxPositiveVelocity();
	fPoint GetMaxNegativeVelocity();
	fPoint GetDir();

	void finalupdate();

private:
	void Move();

};