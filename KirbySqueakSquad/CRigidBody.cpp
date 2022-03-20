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

void CRigidBody::SetMaxSpeed(float maxSpeed)
{
	m_fMaxSpeed = maxSpeed;
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

void CRigidBody::finalupdate()
{
	// 길이를 구함
	float force = m_fForce.Length();
	if (0.f != force)
	{
		// 길이에 질량만큼 나눔(가속도 구해줌)
		float accel = force / m_fMass;
		// 가속도에 방향을 정해줌
		m_fAccel = m_fForce.normalize() * accel;
	}
	// 중력가속도 적용
	m_fAccel += m_fGAccel;
	// 속력에 넣어줌
	m_fVelocity += m_fAccel * fDT;
	// 마찰력 적용
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
		// 같은 방향의 크기 max로 바꿔줌
		m_fVelocity = m_fVelocity.normalize() * m_fMaxSpeed;
	}
	Move();
	// 힘을 준 순간에만 영향을 주도록 초기화
	m_fForce = fPoint(0.f, 0.f);
	m_fAccel = fPoint(0.f, 0.f);
	m_fGAccel = fPoint(0.f, 0.f);
}


void CRigidBody::Move()
{
	// 이동 속력
	float fSpeed = m_fVelocity.Length();
	if (0.f != fSpeed)
	{
		fPoint pos = m_pOwner->GetPos();
		pos += m_fVelocity * fDT;
		if (0 <= pos.x && pos.x <= CCameraManager::getInst()->GetDisLimmit().x)
			m_pOwner->SetPos(pos);
	}
}
