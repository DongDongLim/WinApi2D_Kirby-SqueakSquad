#pragma once

class CGameObject;

class CRigidBody
{
	friend class CGameObject;
private:
	CGameObject* m_pOwner;	// ����
	fPoint m_fForce;		// ���⿡ ����Ǵ� ��
	fPoint m_fAccel;		// ���ӵ�
	fPoint m_fVelocity;		// �ӵ�
	fPoint m_fGAccel;		// �߷°��ӵ�
	fPoint m_fPositiveMaxVelocity;	// ���� �ִ� �ӷ�
	fPoint m_fNegativeMaxVelocity;	// ���� �ִ� �ӷ�
	float m_fMass;			// ����
	float m_fFricCoeff;		// ������
	float m_fDelayTime;		// ������Ʈ ������

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