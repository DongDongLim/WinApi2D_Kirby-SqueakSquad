#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"

CPlayerIdle::CPlayerIdle()
{

}

CPlayerIdle::~CPlayerIdle()
{

}

void CPlayerIdle::update()
{

}

void CPlayerIdle::Enter()
{
	GetAnimator()->Play(L"Idle");
}

void CPlayerIdle::Exit()
{

}