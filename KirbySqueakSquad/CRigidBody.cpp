#include "framework.h"
#include "CRigidBody.h"
#include "CGameObject.h"
#include "CGravity.h"

CRigidBody::CRigidBody()
{
	m_pOwner = nullptr;
	m_fFricCoeff = 1.f;
	m_fMass = 0.f;
	m_fPositiveMaxVelocity = fPoint(75.f, 200.f);
	m_fNegativeMaxVelocity = fPoint(-75.f, -200.f);
	m_fDelayTime = 0.01f;
}

CRigidBody::CRigidBody(const CRigidBody& other)
{
	m_pOwner = nullptr;
	m_fFricCoeff = 1.f;
	m_fMass = 0.f;
	m_fPositiveMaxVelocity = fPoint(75.f, 200.f);
	m_fNegativeMaxVelocity = fPoint(-75.f, -200.f);
	m_fDelayTime = 0.01f;
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

void CRigidBody::SetMaxPositiveVelocity(fPoint maxSpeed)
{
	m_fPositiveMaxVelocity = maxSpeed;
}

void CRigidBody::SetMaxNegativeVelocity(fPoint maxSpeed)
{
	m_fNegativeMaxVelocity = maxSpeed;
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

void CRigidBody::RecoveryMaxPositiveVelocity()
{
	m_fPositiveMaxVelocity = fPoint(75.f, 200.f);
}

void CRigidBody::RecoveryMaxNegativeVelocity()
{
	m_fNegativeMaxVelocity = fPoint(-75.f, -200.f);
}

fPoint CRigidBody::GetMaxPositiveVelocity()
{
	return m_fPositiveMaxVelocity;
}

fPoint CRigidBody::GetMaxNegativeVelocity()
{
	return m_fNegativeMaxVelocity;
}

fPoint CRigidBody::GetDir()
{
	return m_fVelocity.normalize();
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
	if (nullptr != m_pOwner->GetGravity())
	{
		if(!m_pOwner->GetGravity()->GetIsGround())
			m_fAccel += m_fGAccel;
	}

	// �ӷ¿� �־���
	m_fVelocity += m_fAccel * fDT;
	if (abs(m_fPrevVelocity.y - m_fVelocity.y) > 10.f)
	{
		int a = 0;
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

	if (m_fVelocity.x > 0)
	{
		if (m_fPositiveMaxVelocity.x < m_fVelocity.x)
		{
			m_fVelocity.x = m_fPositiveMaxVelocity.x;
		}
	}
	else
	{
		if (m_fNegativeMaxVelocity.x > m_fVelocity.x)
		{
			m_fVelocity.x = m_fNegativeMaxVelocity.x;
		}

	}
	if (m_fVelocity.y > 0)
	{
		if (m_fPositiveMaxVelocity.y < m_fVelocity.y)
		{
			m_fVelocity.y = m_fPositiveMaxVelocity.y;
		}
	}
	else
	{
		if (m_fNegativeMaxVelocity.y > m_fVelocity.y)
		{
			m_fVelocity.y = m_fNegativeMaxVelocity.y;
		}
	}
	Move();
	m_fPrevVelocity = m_fVelocity;
	// ���� �� �������� ������ �ֵ��� �ʱ�ȭ
	m_fForce = fPoint(0.f, 0.f);
	m_fAccel = fPoint(0.f, 0.f);
	m_fGAccel = fPoint(0.f, 0.f);
}


void CRigidBody::Move()
{
	/*m_fDelayTime -= fDT;
	if (m_fDelayTime <= 0)
	{*/
		// �̵� �ӷ�
		float fSpeed = m_fVelocity.Length();
		if (0.f != fSpeed)
		{
			fPoint pos = m_pOwner->GetPos();
			pos += m_fVelocity * fDT;
			if (0 <= pos.x && pos.x <= CCameraManager::getInst()->GetDisLimmit().x)
				m_pOwner->SetPos(pos);
		}
		/*m_fDelayTime = 0.01f;
	}*/
}
