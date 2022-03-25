#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CDeadState.h"
#include "CGravity.h"
#include "CRigidBody.h"

CMonster::CMonster()
{
	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"MonsterTex", L"texture\\Animation\\sprite0.png");

	m_pAI = nullptr;
	m_bIsEaten = false;

	SetName(L"Monster");
	SetScale(fPoint(32.f, 32.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(17.f, 17.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 7.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"MonsterStand", m_pImg, fPoint(0.f, 0.f),
		fPoint(32.f, 32.f),
		fPoint(0.f, 0.f), 0.5f, 1);
	GetAnimator()->Play(L"MonsterStand");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"MonsterStand");
	pAni->GetFrame(0).fptOffset = fPoint(0.f, 5.f);
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}

CMonster* CMonster::Clone()
{
	CMonster* newMonster = new CMonster;
	if (nullptr != m_pAI)
	{
		newMonster->m_pAI = new AI;
	}
	return new CMonster(*newMonster);
}

CMonster* CMonster::Create(MON_TYPE type, fPoint pos)
{
	CMonster* pMon = nullptr;

	switch (type)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);
		pMon->SetType(type);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->AddState(new CDeadState(STATE_MON::DEAD));
		pAI->SetCurState(STATE_MON::IDLE);
		pAI->SetStartPos(pMon->GetPos());
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::CUTTER:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);
		pMon->SetType(type);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->AddState(new CDeadState(STATE_MON::DEAD));
		pAI->SetCurState(STATE_MON::IDLE);
		pAI->SetStartPos(pMon->GetPos());
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
		break;
	case MON_TYPE::THROW:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);
		pMon->SetType(type);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->AddState(new CDeadState(STATE_MON::DEAD));
		pAI->SetCurState(STATE_MON::IDLE);
		pAI->SetStartPos(pMon->GetPos());
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
		break;
	default:
		break;
	}
	assert(pMon);
	return pMon;
}

void CMonster::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	component_render();
}

void CMonster::update()
{
	if (nullptr != GetAnimator())
		GetAnimator()->update();
}

void CMonster::finalupdate()
{
	if (nullptr != m_pAI)
		m_pAI->update();
	if (nullptr != GetGravity())
	{
		GetGravity()->finalupdate();
	}
	if (nullptr != GetRigidBody())
	{
		GetRigidBody()->finalupdate();
	}
	if (nullptr != GetCollider())
	{
		GetCollider()->finalupdate();
	}
}

float CMonster::GetSpeed()
{
	return m_tInfo.fSpeed;
}

const tMonInfo& CMonster::GetMonInfo()
{
	return m_tInfo;
}

void CMonster::SetIsEaten(bool isEaten)
{
	m_bIsEaten = isEaten;
}

void CMonster::SetSpeed(float speed)
{
	m_tInfo.fSpeed = speed;
}

void CMonster::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CMonster::SetMonInfo(const tMonInfo& info)
{
	m_tInfo = info;
}
void CMonster::SetEaten(bool isEaten)
{
	m_bIsEaten = isEaten;
}

void CMonster::SetType(MON_TYPE type)
{
	m_eType = type;
}

void CMonster::SetRegenPosX(float posX)
{
	m_fRegenPosX = posX;
}

MON_TYPE CMonster::GetType()
{
	return MON_TYPE();
}

bool CMonster::GetIsEaten()
{
	return m_bIsEaten;
}

float CMonster::GetRegenPosX()
{
	return m_fRegenPosX;
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_tInfo.fHP -= 1;
		if (m_tInfo.fHP <= 0)
			DeleteObj(this);
	}
}