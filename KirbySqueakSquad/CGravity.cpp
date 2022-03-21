#include "framework.h"
#include "CGravity.h"
#include "CGameObject.h"
#include "CRigidBody.h"
#include "CPlayer.h"


CGravity::CGravity()
{
	m_pOwner = nullptr;
	m_bisGround = false;
	m_fGAccel = fPoint(0.f, 500.f);
}

CGravity::~CGravity()
{
}

void CGravity::SetIsGround(bool isGround)
{
	m_bisGround = isGround;
}

bool CGravity::GetIsGround()
{
	return m_bisGround;
}

void CGravity::finalupdate()
{
	m_pOwner->GetRigidBody()->SetGAccel(m_fGAccel);
	if (!m_bisGround)
		m_pOwner->GetRigidBody()->SetMaxPositiveVelocity(m_fMaxPositiveVelocity);
	else
		m_pOwner->GetRigidBody()->SetMaxPositiveVelocity(fPoint(m_fMaxPositiveVelocity.x, 0));
}
