#include "framework.h"
#include "CRigidBody.h"
#include "CGameObject.h"

CRigidBody::CRigidBody()
{
	m_pOwner = nullptr;
	m_fFricCoeff = 50.f;
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

void CRigidBody::SetMaxSpeed(fPoint maxSpeed)
{
	m_fMaxVelocity = maxSpeed;
}

void CRigidBody::SetFricCoeff(float fricCoeff)
{
	m_fFricCoeff = fricCoeff;
}

fPoint CRigidBody::GetVelocity()
{
	return m_fVelocity;
}

void CRigidBody::SetGAccel(fPoint gAccel)
{
	m_fGAccel = gAccel;
}

fPoint CRigidBody::GetMaxVelocity()
{
	return m_fMaxVelocity;
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
	}
	// �߷°��ӵ� ����
	m_fAccel += m_fGAccel;
	// �ӷ¿� �־���
	m_fVelocity += m_fAccel * fDT;
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

	if (abs(m_fMaxVelocity.x) < abs(m_fVelocity.x))
	{
		// ���� ������ ũ�� max�� �ٲ���
		// max�� �ٲ��ַ��� ���� ������ max�ٲ�����ؼ�
		// �������� / ���밪(��������)�̸� +-�� ����, ���� 1�ϵǾ�
		// �������� max�� �� �� ����
		m_fVelocity.x = m_fVelocity.x/ abs(m_fVelocity.x) * m_fMaxVelocity.x;
	}
	if (abs(m_fMaxVelocity.y) < abs(m_fVelocity.y))
	{
		m_fVelocity.y = m_fVelocity.y / abs(m_fVelocity.y) * m_fMaxVelocity.y;
	}
	Move();
	// ���� �� �������� ������ �ֵ��� �ʱ�ȭ
	m_fForce = fPoint(0.f, 0.f);
	m_fAccel = fPoint(0.f, 0.f);
	m_fGAccel = fPoint(0.f, 0.f);
}


void CRigidBody::Move()
{
	// �̵� �ӷ�
	float fSpeed = m_fVelocity.Length();
	if (0.f != fSpeed)
	{
		fPoint pos = m_pOwner->GetPos();
		pos += m_fVelocity * fDT;
		if (0 <= pos.x && pos.x <= CCameraManager::getInst()->GetDisLimmit().x)
			m_pOwner->SetPos(pos);
	}
}
