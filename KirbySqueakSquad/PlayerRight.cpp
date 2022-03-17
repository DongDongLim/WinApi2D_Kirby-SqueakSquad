#include "framework.h"
#include "CPlayer.h"

struct rightrdata
{
	int a;
};

void CPlayer::PlayerRight(DWORD_PTR, DWORD_PTR)
{
	rightrdata data;
	data.a = 1;
	m_dir = 1;
}