#include "framework.h"
#include "CPlayer.h"

void CPlayer::PlayerLeft(DWORD_PTR, DWORD_PTR)
{
	m_dir = -1;
}