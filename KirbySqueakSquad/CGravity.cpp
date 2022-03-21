#include "framework.h"
#include "CGravity.h"
#include "CGameObject.h"
#include "CRigidBody.h"


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
	if (!m_bisGround)
		m_pOwner->GetRigidBody()->SetGAccel(m_fGAccel);
	//else
		//m_pOwner->GetRigidBody()->SetGAccel(fPoint(0, 0));
}
