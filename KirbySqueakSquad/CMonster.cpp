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
#include "CGravity.h"
#include "CScene.h"
#include "CInhaleState.h"

CMonster::CMonster()
{
	m_pAI = nullptr;
	m_bIsEaten = false;

	SetName(L"Monster");

	CreateCollider();
	CreateGravity();
	CreateRigidBody();
	GetRigidBody()->SetMass(1);
	GetRigidBody()->SetMaxPositiveVelocity(fPoint(50.f, 200.f));
	GetRigidBody()->SetMaxNegativeVelocity(fPoint(-50.f, -200.f));
	CreateAnimator();	
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
		pMon->SetGroup(GROUP_GAMEOBJ::MONSTER);
		pMon->SetPos(pos);
		pMon->SetType(type);
		pMon->SetScale(fPoint(32.f, 32.f));
		pMon->GetCollider()->SetScale(fPoint(17.f, 17.f));

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
		pAI->AddState(new CInhaleState(STATE_MON::INHALE));
		pAI->SetCurState(STATE_MON::IDLE);
		pAI->SetStartPos(pMon->GetPos());
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::CUTTER:
	{
		pMon = new CMonster;
		pMon->SetGroup(GROUP_GAMEOBJ::MONSTER);
		pMon->SetPos(pos);
		pMon->SetType(type);
		pMon->SetScale(fPoint(32.f, 32.f));
		pMon->GetCollider()->SetScale(fPoint(17.f, 17.f));
		pMon->GetCollider()->SetOffsetPos(fPoint(0.f, 7.f));

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 5.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->AddState(new CDeadState(STATE_MON::DEAD));
		pAI->AddState(new CInhaleState(STATE_MON::INHALE));
		pAI->SetCurState(STATE_MON::IDLE);
		pAI->SetStartPos(pMon->GetPos());
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);

		CD2DImage* pImg = CResourceManager::getInst()->
			LoadD2DImage(L"CutterM", L"texture\\Animation\\CutterMonSprite.png");
		wstring keepPath = CPathManager::getInst()->GetContentPath();
		wstring path = keepPath;
		path += L"anim\\CMonIdle.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg); 
		path = keepPath;
		path += L"anim\\CMonMove.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = keepPath;
		path += L"anim\\CMonAttack0.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = keepPath;
		path += L"anim\\CMonAttack1.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = keepPath;
		path += L"anim\\CMonDamage.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = keepPath;
		path += L"anim\\CMonAttackEffect.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		pMon->GetAnimator()->Play(L"CMonIdle");
	}
		break;
	case MON_TYPE::THROW:
	{
		pMon = new CMonster;
		pMon->SetGroup(GROUP_GAMEOBJ::MONSTER);
		pMon->SetPos(pos);
		pMon->SetType(type);
		pMon->SetScale(fPoint(54.f, 54.f));
		pMon->GetCollider()->SetScale(fPoint(33.f, 33.f));

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 5.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->AddState(new CDeadState(STATE_MON::DEAD));
		pAI->AddState(new CInhaleState(STATE_MON::INHALE));
		pAI->SetCurState(STATE_MON::IDLE);
		pAI->SetStartPos(pMon->GetPos());
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
		CD2DImage* pImg = CResourceManager::getInst()->
			LoadD2DImage(L"ThrowM", L"texture\\Animation\\ThrowMonSprite.png");
		wstring path = CPathManager::getInst()->GetContentPath();
		path += L"anim\\TMonIdle.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = CPathManager::getInst()->GetContentPath();
		path += L"anim\\TMonHold.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = CPathManager::getInst()->GetContentPath();
		path += L"anim\\TMonDamage.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = CPathManager::getInst()->GetContentPath();
		path += L"anim\\TMonAttack2.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = CPathManager::getInst()->GetContentPath();
		path += L"anim\\TMonAttackEffect.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = CPathManager::getInst()->GetContentPath();
		path += L"anim\\TMonAttack1.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = CPathManager::getInst()->GetContentPath();
		path += L"anim\\TMonAttack0.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = CPathManager::getInst()->GetContentPath();
		path += L"anim\\TMonCatch.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		path = CPathManager::getInst()->GetContentPath();
		path += L"anim\\TMonMove.Anim";
		CSceneManager::getInst()->GetCurScene()->LoadAnim(path, pMon, pImg);
		pMon->GetAnimator()->Play(L"TMonIdle");
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
	return m_eType;
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