#include "framework.h"
#include "CRigidBody.h"
#include "CGameObject.h"

CRigidBody::CRigidBody()
{
	m_pOwner = nullptr;
}

CRigidBody::CRigidBody(const CRigidBody& other)
{
	m_pOwner = nullptr;
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

void CRigidBody::finalupdate()
{
	float force = m_fForce.Length();
	if (0.f != force)
	{
		float accel = force / m_fMass;
		m_fAccel = m_fForce.normalize() * accel;
		m_fVelocity += m_fAccel * fDT;
	}
	Move();
}


void CRigidBody::Move()
{
	// 이동 속력
	float fSpeed = m_fVelocity.Length();
	if (0.f != fSpeed)
	{
		fPoint pos = m_pOwner->GetPos();
		pos += m_fVelocity * fDT;

		m_pOwner->SetPos(pos);
	}
}
