#include "framework.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CAnimator.h"

void CPlayer::PlayerMove(DWORD_PTR, DWORD_PTR)
{
	fPoint pos = GetPos();
	GetAnimator()->SetReverse(m_dir < 0 ? true : false);
	GetAnimator()->Play(L"Move");

	pos.x += m_dir * m_fVelocity * fDT;

	SetPos(pos);
}
