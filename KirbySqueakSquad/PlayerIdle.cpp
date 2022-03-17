#include "framework.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CAnimator.h"

void CPlayer::PlayerIdle(DWORD_PTR, DWORD_PTR)
{
	GetAnimator()->Play(L"Idle");
}