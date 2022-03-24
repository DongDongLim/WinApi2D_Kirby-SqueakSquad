#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CPlayer.h"
#include "CGravity.h"


CPlayerDown::CPlayerDown()
{
	m_eState = PLAYERSTATE::DOWN;
}

CPlayerDown::~CPlayerDown()
{

}

void CPlayerDown::Anim()
{
	if (Key(VK_DOWN))
	{
		m_pPlayer->GetAnimator()->Play(L"Down");
	}
}

void CPlayerDown::update()
{
	CCollider* collider = m_pPlayer->GetCollider();
	if (KeyDown('C') || KeyDown('X') || KeyDown('V'))
	{
		collider->SetOffsetPos(fPoint(collider->GetOffsetPos().x, collider->GetOffsetPos().y - collider->GetScale().y / 2));
		collider->SetScale(fPoint(collider->GetScale().x, collider->GetScale().y * 2));
		CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::ATTACK);
	}
	else if (KeyUp(VK_DOWN))
	{
		collider->SetOffsetPos(fPoint(collider->GetOffsetPos().x, collider->GetOffsetPos().y - collider->GetScale().y / 2));
		collider->SetScale(fPoint(collider->GetScale().x, collider->GetScale().y * 2));
		Exit(PLAYERSTATE::IDLE);
	}
}

void CPlayerDown::Enter()
{
	m_bIsActive = true;
	m_startDir = m_pPlayer->GetDir();
	CCollider* collider = m_pPlayer->GetCollider();
	collider->SetOffsetPos(fPoint(collider->GetOffsetPos().x, collider->GetOffsetPos().y + collider->GetScale().y / 4));
	collider->SetScale(fPoint(collider->GetScale().x, collider->GetScale().y / 2));
}

void CPlayerDown::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	if (state != PLAYERSTATE::END)
		CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}