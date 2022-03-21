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
	fPoint m_fMaxVelocity;		// �ִ� �ӷ�
	float m_fMass;			// ����
	float m_fFricCoeff;		// ������

public:
	CRigidBody();
	CRigidBody(const CRigidBody& other);
	~CRigidBody();

	void AddForce(fPoint force);
	void SetMass(float mass);
	float GetMass();
		
	void SetVelocity(fPoint velocity);
	void AddVelocity(fPoint velocity);
	void SetMaxSpeed(fPoint maxVelocity);
	void SetFricCoeff(float fricCoeff);
	void SetGAccel(fPoint gAceel);

	fPoint GetVelocity();
	fPoint GetMaxVelocity();
	fPoint GetDir();

	void finalupdate();

private:
	void Move();

};