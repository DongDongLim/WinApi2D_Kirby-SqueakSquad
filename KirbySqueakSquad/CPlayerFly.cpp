#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"
#include "CGravity.h"


CPlayerFly::CPlayerFly()
{
	m_eState = PLAYERSTATE::FLY;
	m_fAnimSpeed = 0;
	m_fKeepTimer = m_fAnimSpeed;
}

CPlayerFly::~CPlayerFly()
{

}

void CPlayerFly::Anim()
{
	if (Key(VK_UP) || Key('X') || Key('V'))
	{
		m_pPlayer->GetAnimator()->Play(L"UpMove");
	}
	else
	{
		m_pPlayer->GetAnimator()->Play(L"UpIdle");
	}
}

void CPlayerFly::KeyUpdate()
{
	if (Key(VK_UP) || Key('X') || Key('V'))
	{
		m_pPlayer->GetRigidBody()->SetVelocity(fPoint(m_pPlayer->GetRigidBody()->GetVelocity().x, -150.f));
	}
	else
	{
		if (!m_pPlayer->GetGravity()->GetIsGround())
			m_pPlayer->GetRigidBody()->AddVelocity(fPoint(0, -70.f));
	}
	m_fKeepTimer = m_fAnimSpeed;
}

void CPlayerFly::update()
{
	m_fKeepTimer -= fDT;
	if (m_fKeepTimer <= 0)
		KeyUpdate();
}

void CPlayerFly::Enter()
{
	m_bIsActive = true;
	m_pPlayer->GetAnimator()->Play(L"UpMove");
	m_fAnimSpeed = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
	m_fKeepTimer = 0.f;
}

void CPlayerFly::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
}