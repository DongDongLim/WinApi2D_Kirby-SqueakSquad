#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayer.h"
#include "CAttackObj.h"
#include "CScene.h"
#include "CRigidBody.h"

CPlayerAttack::CPlayerAttack()
{
	m_eState = PLAYERSTATE::ATTACK;
	m_pPlayer->GetAnimator()->Play(L"InHale0");
	nomalanimtime = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
	nomalanimKeeptime = nomalanimtime;
	m_fAttRange = fPoint(0, 0);
	for (int i = 0; i < 4; ++i)
	{
		m_pAttackobj[i] = new CAttackObj();
		CSceneManager::getInst()->GetCurScene()->
			AddObject(m_pAttackobj[i], GROUP_GAMEOBJ::MISSILE_PLAYER);
	}
	CCollisionManager::getInst()->CheckGroup(
		GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);
}

CPlayerAttack::~CPlayerAttack()
{

}


void CPlayerAttack::NomalAttack()
{
	if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"Up")
	{
		if (0 >= nomalanimtime)
		{
			Exit(PLAYERSTATE::Fall);
		}
	}
	else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"DownSlide")
	{
		int dir = 0;
		int prev = 0;
		int cur = 0;
		m_startDir ? dir = 5 : dir = -5;
		m_startDir ? prev = 1 : prev = -1;
		if (nomalanimtime < 0 && -0.5 <= nomalanimtime)
			m_pPlayer->GetRigidBody()->AddVelocity(fPoint(dir * -nomalanimtime, 0));
		else if(-0.5 > nomalanimtime)
		{
			m_pPlayer->GetRigidBody()->AddVelocity(fPoint(dir * nomalanimtime, 0));
		}
		if (m_pPlayer->GetRigidBody()->GetDir().x != 0)
			m_pPlayer->GetRigidBody()->GetDir().x > 0 ? cur = 1 : cur = -1;
		
		if ((cur != 0) && (prev != cur))
		{
			m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0, 0));
			if (Key(VK_DOWN))
				Exit(PLAYERSTATE::DOWN);
			else
				Exit(PLAYERSTATE::IDLE);
		}
	}
	else
	{
		if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale0")
		{
			m_pAttackobj[0]->SetRange(fPoint(64.f, 48.f));
			if (!Key('C'))
			{
				if (nullptr != m_pAttackobj[0])
					m_pAttackobj[0]->Exit();
				m_pPlayer->GetAnimator()->Play(L"InHale1");
			}
		}
		else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale1")
		{
			m_pAttackobj[0]->SetRange(fPoint(64.f, 48.f));
			if (!Key('C'))
			{
				m_pPlayer->GetAnimator()->Play(L"InHale3");
				nomalanimKeeptime = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
				nomalanimtime = nomalanimKeeptime;
			}
		}
		else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale2")
		{
			m_pAttackobj[0]->SetRange(fPoint(80.f, 64.f));
			if (!Key('C'))
			{
				m_pPlayer->GetAnimator()->Play(L"InHale3");
				nomalanimKeeptime = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
				nomalanimtime = nomalanimKeeptime;
			}
		}
	}
}


void CPlayerAttack::update()
{
	NomalAttack();
	
}

void CPlayerAttack::Anim()
{
	nomalanimtime -= fDT;
	m_pPlayer->GetAnimator()->SetReverce(!m_startDir);
	if (0 >= nomalanimtime)
	{
		if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"DownSlide")
		{
			m_pPlayer->GetAnimator()->Stop();
		}
		else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale0")
		{
			m_pPlayer->GetAnimator()->Play(L"InHale1");
			nomalanimKeeptime = 0.5f;
			nomalanimtime = nomalanimKeeptime;
		}
		else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale1")
		{
			m_pPlayer->GetAnimator()->Play(L"InHale2");
			nomalanimKeeptime = 1.f;
			nomalanimtime = nomalanimKeeptime;
		}
		else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale2")
		{
			m_pPlayer->GetAnimator()->Play(L"InHale3");
			nomalanimKeeptime = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
			nomalanimtime = nomalanimKeeptime;
		}
		else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale3")
		{
			if (nullptr != m_pAttackobj[0])
				m_pAttackobj[0]->Exit();
			Exit(PLAYERSTATE::IDLE);
		}
	}
}

void CPlayerAttack::Enter()
{
	m_bIsActive = true;
	if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::FLY))
	{
		m_pPlayer->GetAnimator()->ReversePlay(L"Up");
		CStateManager::getInst()->FindPlayeState(PLAYERSTATE::FLY)->Exit(PLAYERSTATE::END);
	}
	else if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::DOWN))
	{
		m_pPlayer->GetAnimator()->ReversePlay(L"DownSlide");
		CStateManager::getInst()->FindPlayeState(PLAYERSTATE::DOWN)->Exit(PLAYERSTATE::END);
	}
	else
	{
		m_pPlayer->GetAnimator()->Play(L"InHale0");
		m_pAttackobj[0]->Enter();
	}
	nomalanimtime = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
	nomalanimKeeptime = nomalanimtime;
	m_startDir = m_pPlayer->GetDir();

}

void CPlayerAttack::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	if (state != PLAYERSTATE::END)
		CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}