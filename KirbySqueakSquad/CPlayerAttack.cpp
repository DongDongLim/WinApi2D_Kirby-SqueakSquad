#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayer.h"
#include "CAttackObj.h"
#include "CScene.h"
#include "CRigidBody.h"
#include "CGravity.h"

CPlayerAttack::CPlayerAttack()
{
	m_eState = PLAYERSTATE::ATTACK;
	nomalanimtime = 0;
	nomalanimKeeptime = nomalanimtime;
	m_fAttRange = fPoint(0, 0);
	for (int i = 0; i < 8; ++i)
	{
		m_pAttackobj[i] = new CAttackObj();
		CSceneManager::getInst()->GetCurScene()->
			AddObject(m_pAttackobj[i], GROUP_GAMEOBJ::MISSILE_PLAYER);
	}
	CCollisionManager::getInst()->CheckGroup(
		GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(
		GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::TILE);
}

CPlayerAttack::~CPlayerAttack()
{
	for (int i = 0; i < 4; ++i)
	{
		if (nullptr != m_pAttackobj[i])
			m_pAttackobj[i] = nullptr;
	}
}

void CPlayerAttack::CutterAttack()
{
	if (!Key('C'))
	{
		Exit(PLAYERSTATE::IDLE);
	}

}

void CPlayerAttack::ThrowAttack()
{
}

void CPlayerAttack::NomalAnim()
{
	if (0 >= nomalanimtime)
	{
		if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale0")
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
	else
	{
		if (!Key('C'))
		{
			m_pPlayer->GetAnimator()->Play(L"InHale3");
			nomalanimtime = 0;
		}
	}
}

void CPlayerAttack::CutterAnim()
{
	if (0 >= nomalanimtime)
	{
		if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"CAttack0")
		{
			m_pPlayer->GetAnimator()->Play(L"CAttack1");
			nomalanimKeeptime = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
			nomalanimtime = nomalanimKeeptime;
		}
		else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"CAttack1")
		{
			m_pPlayer->GetAnimator()->Stop();
		}
	}
}

void  CPlayerAttack::ThrowAnim()
{
	if (0 >= nomalanimtime)
	{
		if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"TAttackSet")
		{
			m_pPlayer->GetAnimator()->Play(L"TAttackSet0");
		}
	}
	if (!Key('C'))
	{
		Exit(PLAYERSTATE::IDLE);
	}
}

void CPlayerAttack::NomalAttack()
{
	if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale0")
	{
		m_pAttackobj[0]->SetRange(fPoint(64.f, 48.f));
	}
	else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale1")
	{
		m_pAttackobj[0]->SetRange(fPoint(64.f, 48.f));
	}
	else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale2")
	{
		m_pAttackobj[0]->SetRange(fPoint(80.f, 64.f));
	}
}


void CPlayerAttack::update()
{
	if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == m_pPlayer->GetAnimString().g_wUP)
	{
		if (0 >= nomalanimtime)
		{
			Exit(PLAYERSTATE::IDLE);
		}
	}
	else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == m_pPlayer->GetAnimString().g_wDOWNSLIDE)
	{
		int dir = 0;
		int prev = 0;
		int cur = 0;
		m_startDir ? dir = 5 : dir = -5;
		m_startDir ? prev = 1 : prev = -1;
		if (nomalanimtime < 0 && -0.5 <= nomalanimtime)
			m_pPlayer->GetRigidBody()->AddVelocity(fPoint(dir * -nomalanimtime, 0));
		else if (-0.5 > nomalanimtime)
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
		switch (m_pPlayer->GetAttackType())
		{
		case ATTACK_TYPE::NORMAL:
			NomalAttack();
			break;
		case ATTACK_TYPE::CUTTER:
			CutterAttack();
			break;
		case ATTACK_TYPE::THROW:
			ThrowAttack();
			break;
		case ATTACK_TYPE::SIZE:
			break;
		default:
			break;
		}
	}
}


void CPlayerAttack::Anim()
{
	nomalanimtime -= fDT;
	m_pPlayer->GetAnimator()->SetReverce(!m_startDir);
	if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == m_pPlayer->GetAnimString().g_wUP)
	{

	}
	else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == m_pPlayer->GetAnimString().g_wDOWNSLIDE)
	{
		if (0 >= nomalanimtime)
		{
			m_pPlayer->GetAnimator()->Stop();
		}
	}
	else
	{
		switch (m_pPlayer->GetAttackType())
		{
		case ATTACK_TYPE::NORMAL:
			NomalAnim();
			break;
		case ATTACK_TYPE::CUTTER:
			CutterAnim();
			break;
		case ATTACK_TYPE::THROW:
			ThrowAnim();
			break;
		case ATTACK_TYPE::SIZE:
			break;
		default:
			break;
		}
	}
	
}

void CPlayerAttack::Enter()
{
	m_bIsActive = true;
	if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::FLY))
	{
		m_pPlayer->GetAnimator()->ReversePlay(m_pPlayer->GetAnimString().g_wUP);
		m_pAttackobj[0]->Enter();
		CStateManager::getInst()->FindPlayeState(PLAYERSTATE::FLY)->Exit(PLAYERSTATE::END);
	}
	else if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::DOWN))
	{
		m_pPlayer->GetAnimator()->Play(m_pPlayer->GetAnimString().g_wDOWNSLIDE);
		m_pAttackobj[0]->Enter();
		CStateManager::getInst()->FindPlayeState(PLAYERSTATE::DOWN)->Exit(PLAYERSTATE::END);
	}
	else if (m_pPlayer->GetAttackType() == ATTACK_TYPE::NORMAL)
	{
		if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::EAT))
		{
			m_pPlayer->GetAnimator()->ReversePlay(m_pPlayer->GetAnimString().g_wUP);
			m_pAttackobj[0]->Enter();
			CStateManager::getInst()->FindPlayeState(PLAYERSTATE::EAT)->Exit(PLAYERSTATE::END);
		}
		else
		{
			m_pPlayer->GetAnimator()->Play(L"InHale0");
			m_pAttackobj[0]->Enter();
		}
	}
	else if (m_pPlayer->GetAttackType() == ATTACK_TYPE::CUTTER)
	{
		m_pPlayer->GetAnimator()->Play(L"CAttack0");
		for (int i = 0; i < 8; ++i)
		{
			if (m_pAttackobj[i]->isDead())
			{
				m_pAttackobj[i]->Enter();
				break;
			}

		}
	}
	else if (m_pPlayer->GetAttackType() == ATTACK_TYPE::THROW)
	{
		if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() != L"TAttackSet1")
		{
			m_pPlayer->GetAnimator()->Play(L"TAttackSet");
		}
		for (int i = 0; i < 8; ++i)
		{
			if (m_pAttackobj[i]->isDead())
			{
				m_pAttackobj[i]->Enter();
				break;
			}
		}
	}
	nomalanimtime = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
	nomalanimKeeptime = nomalanimtime;
	m_startDir = m_pPlayer->GetDir();

}

void CPlayerAttack::Exit(PLAYERSTATE state)
{
	for (int i = 0; i < 8; ++i)
	{
		if (!m_pAttackobj[i]->isDead())
		{
			if (MOVETYPE::FIX == m_pAttackobj[i]->GetMoveType())
			{
				m_pAttackobj[i]->Exit();
				break;
			}
		}
	}
	m_bIsActive = false;
	if (state != PLAYERSTATE::END)
		CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}