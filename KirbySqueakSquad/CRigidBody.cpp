#include "framework.h"
#include "CRigidBody.h"
#include "CGameObject.h"

CRigidBody::CRigidBody()
{
	m_pOwner = nullptr;
	m_fFricCoeff = 10.f;
}

CRigidBody::CRigidBody(const CRigidBody& other)
{
	m_pOwner = nullptr;
	m_fFricCoeff = 10.f;
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::AddForce(fPoint force)
{
	m_fForce += force;
}

void CRigidBody::SetMass(float mass)
{
	m_fMass = mass;
}

float CRigidBody::GetMass()
{
	return m_fMass;
}

void CRigidBody::SetVelocity(fPoint velocity)
{
	m_fVelocity = velocity;
}


void CRigidBody::AddVelocity(fPoint velocity)
{
	m_fVelocity += velocity;
}

void CRigidBody::SetMaxSpeed(float maxSpeed)
{
	m_fMaxSpeed = maxSpeed;
}

void CRigidBody::SetFricCoeff(float fricCoeff)
{
	m_fFricCoeff = fricCoeff;
}

void CRigidBody::finalupdate()
{
	// ���̸� ����
	float force = m_fForce.Length();
	if (0.f != force)
	{
		// ���̿� ������ŭ ����(���ӵ� ������)
		float accel = force / m_fMass;
		// ���ӵ��� ������ ������
		m_fAccel = m_fForce.normalize() * accel;
		// �ӷ¿� �־���
		m_fVelocity += m_fAccel * fDT;
	}
	// ������ ����
	if (!m_fVelocity.IsZero())
	{
		fPoint fricDir = m_fVelocity;
		fPoint friction = fricDir.normalize() * (-1) * m_fFricCoeff * fDT;

		if (m_fVelocity.Length() <= friction.Length())
		{
			m_fVelocity = fPoint(0.f, 0.f);
		}
		else
		{
			m_fVelocity = m_fVelocity + friction;
		}
	}

	if (m_fMaxSpeed < m_fVelocity.Length())
	{
		// ���� ������ ũ�� max�� �ٲ���
		m_fVelocity = m_fVelocity.normalize() * m_fMaxSpeed;
	}
	Move();
	// ���� �� �������� ������ �ֵ��� �ʱ�ȭ
	m_fForce = fPoint(0.f, 0.f);
}


void CRigidBody::Move()
{
	// �̵� �ӷ�
	float fSpeed = m_fVelocity.Length();
	if (0.f != fSpeed)
	{
		fPoint pos = m_pOwner->GetPos();
		pos += m_fVelocity * fDT;

		m_pOwner->SetPos(pos);
	}
}
