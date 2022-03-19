#pragma once

class CGameObject;

class CRigidBody
{
	friend class CGameObject;
private:
	CGameObject* m_pOwner;	// ����
	fPoint m_fForce;		// ���⿡ ����Ǵ� ��
	fPoint m_fAccel;		// ����
	fPoint m_fVelocity;		// �ӵ�
	float m_fMass;			// ����
	float m_fFricCoeff;		// ������
	float m_fMaxSpeed;		// �ִ� �ӷ�

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

	void finalupdate();

private:
	void Move();

};