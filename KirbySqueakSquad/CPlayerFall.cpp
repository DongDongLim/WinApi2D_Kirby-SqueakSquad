#include "framework.h"
#include "CPlayerState.h"
#include "CStateManager.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CTile.h"
#include "CAnimator.h"
#include "CGravity.h"

CPlayerFall::CPlayerFall()
{
	m_eState = PLAYERSTATE::Fall;
	m_eTarget = COLLIONTARGET::END;
}

CPlayerFall::~CPlayerFall()
{

}

void CPlayerFall::SetTarget(COLLIONTARGET target)
{
	m_eTarget = target;
}



void CPlayerFall::update()
{
	if (m_pPlayer->GetGravity()->GetIsGround())
	{
		if (nullptr == CStateManager::getInst()->FindPlayeState(PLAYERSTATE::ATTACK))
			Exit(PLAYERSTATE::IDLE);
		else
			m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0, 0));
	}
	else
		KeyUpdate();

}

void CPlayerFall::KeyUpdate()
{
	if (KeyDown(VK_UP) || KeyDown('X') || KeyDown('V'))
	{
		Exit(PLAYERSTATE::FLY);
	}
	if (KeyDown('C'))
	{
		if (nullptr == CStateManager::getInst()->FindPlayeState(PLAYERSTATE::FLY))
		{
			Exit(PLAYERSTATE::ATTACK);
		}
	}
}

void CPlayerFall::Anim()
{
	m_pPlayer->GetAnimator()->Play(m_pPlayer->GetAnimString().g_wFALL0);
}

void CPlayerFall::Enter()
{
	m_eTarget = COLLIONTARGET::END;
	m_bIsActive = true;
}

void CPlayerFall::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);	
}