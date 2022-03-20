#include "framework.h"
#include "CGravity.h"

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
}
