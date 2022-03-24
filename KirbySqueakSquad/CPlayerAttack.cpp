#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayer.h"
#include "CAttackObj.h"
#include "CScene.h"

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

void CPlayerAttack::update()
{
	if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"InHale0")
	{
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

void CPlayerAttack::Anim()
{
	nomalanimtime -= fDT;
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
			m_pAttackobj[0]->Exit();
			Exit(PLAYERSTATE::IDLE);
		}
	}
}

void CPlayerAttack::Enter()
{
	m_bIsActive = true;
	m_pPlayer->GetAnimator()->Play(L"InHale0");
	nomalanimtime = m_pPlayer->GetAnimator()->GetAnimSize() * m_pPlayer->GetAnimator()->GetFrameSpeed();
	nomalanimKeeptime = nomalanimtime;
	m_pAttackobj[0]->Enter();
}

void CPlayerAttack::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	if (state != PLAYERSTATE::END)
		CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}