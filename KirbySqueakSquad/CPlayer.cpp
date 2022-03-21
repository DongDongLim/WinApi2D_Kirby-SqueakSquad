#include "framework.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CD2DImage.h"
#include "CState.h"
#include "CPlayerState.h"
#include "CTile.h"


float nomalanimtime = 1.f;
bool start = false;



// 애니메이션 나누는 기능 되나 확인용으로 짬
void CPlayer::PlayerAttack(DWORD_PTR, DWORD_PTR)
{
	if (!start)
	{
		GetAnimator()->Play(L"InHale0");
		nomalanimtime = GetAnimator()->GetAnimSize() * GetAnimator()->GetFrameSpeed();
		start = true;
	}
	else
	{
		nomalanimtime -= fDT;
		if (0 >= nomalanimtime)
		{
			if (GetAnimator()->GetCurAnim()->GetName() == L"InHale0")
			{
				GetAnimator()->Play(L"InHale1");
				nomalanimtime = 1.f;
			}
			else if (GetAnimator()->GetCurAnim()->GetName() == L"InHale1")
			{
				GetAnimator()->Play(L"InHale2");
				nomalanimtime = 1.f;
			}
			else if (GetAnimator()->GetCurAnim()->GetName() == L"InHale2")
			{
				GetAnimator()->Play(L"InHale3");
				nomalanimtime = GetAnimator()->GetAnimSize() * GetAnimator()->GetFrameSpeed();
			}
			else if (GetAnimator()->GetCurAnim()->GetName() == L"InHale3")
			{
				start = false;
				//CStateManager::getInst()->ChangeState(PLAYERSTATE::IDLE);
					
			}
		}
	}
	
}

CPlayer::CPlayer()
{
	//m_bIsGroundCount = 0;
	CStateManager::getInst()->SetPlayer(this);
	m_colliderState = 0;
	m_colliderEnterState = 0;
	m_colliderExitState = 0;
	m_bIsRight = true;
	m_bIsGround = false;
	m_bIsWall[0] = false;
	m_bIsWall[1] = false;

	SetName(L"Player");
	SetScale(fPoint(32.f, 32.f));

	// 콜라이더
	CreateCollider();
	GetCollider()->SetScale(fPoint(19.f, 17.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 7.f));

	// 애니메이션
	m_wImgKey.push_back(L"PlayerImg0");
	m_wImgKey.push_back(L"PlayerImg1");
	m_wImgKey.push_back(L"PlayerImg2");
	m_wImgKey.push_back(L"PlayerImg3");
	m_wImgKey.push_back(L"PlayerImg4");
	m_wImgKey.push_back(L"PlayerImg5");
	m_wImgKey.push_back(L"PlayerImg6");
	m_wImgKey.push_back(L"PlayerImg7");
	m_wImgKey.push_back(L"PlayerImg8");


	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[0], L"texture\\Animation\\sprite0.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[1], L"texture\\Animation\\sprite1.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[2], L"texture\\Animation\\sprite2.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[3], L"texture\\Animation\\sprite3.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[4], L"texture\\Animation\\sprite4.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[5], L"texture\\Animation\\sprite5.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[6], L"texture\\Animation\\sprite6.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[7], L"texture\\Animation\\sprite7.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[8], L"texture\\Animation\\sprite8.png"));

	for (int i = 0; i < m_pImg.size(); ++i)
	{
		m_wAnimKey.push_back(new vector<wstring>);
	}

	m_wAnimKey[0]->push_back(L"Idle");
	m_wAnimKey[0]->push_back(L"Down");
	m_wAnimKey[1]->push_back(L"Move");
	m_wAnimKey[2]->push_back(L"Dash");
	m_wAnimKey[2]->push_back(L"QuickStop");
	m_wAnimKey[3]->push_back(L"DownSlide");
	m_wAnimKey[4]->push_back(L"Jump");
	m_wAnimKey[4]->push_back(L"Turn");
	m_wAnimKey[4]->push_back(L"Fall0");
	m_wAnimKey[4]->push_back(L"Fall0_Down");
	m_wAnimKey[4]->push_back(L"Fall1");
	m_wAnimKey[4]->push_back(L"Fall1_Down");
	m_wAnimKey[5]->push_back(L"Eat");
	m_wAnimKey[6]->push_back(L"Up");
	m_wAnimKey[7]->push_back(L"UpIdle");
	m_wAnimKey[7]->push_back(L"UpMove");
	m_wAnimKey[8]->push_back(L"InHale0");
	m_wAnimKey[8]->push_back(L"InHale1");
	m_wAnimKey[8]->push_back(L"InHale2");
	m_wAnimKey[8]->push_back(L"InHale3");

	CreateAnimator();
	float pixelSize = 32.f;

	GetAnimator()->CreateAnimation(
		m_wAnimKey[0]->at(0),
		m_pImg[0],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(0.f, 0.f), 0.5f, 1);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[0]->at(1),
		m_pImg[0],
		fPoint(pixelSize, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(0.f, 0.f), 0.5f, 1);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[2]->at(0),
		m_pImg[2],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 8);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[2]->at(1),
		m_pImg[2],
		fPoint((float)(pixelSize * 8), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.5f, 1);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[4]->at(0),
		m_pImg[4],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(0.f, 0.f), 0.5f, 1);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[4]->at(1),
		m_pImg[4],
		fPoint((float)(pixelSize * 1), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.05f, 4);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[4]->at(2),
		m_pImg[4],
		fPoint((float)(pixelSize * 5), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 2);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[4]->at(3),
		m_pImg[4],
		fPoint((float)(pixelSize * 7), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 3);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[4]->at(4),
		m_pImg[4],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 6);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[7]->at(0),
		m_pImg[7],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 2);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[7]->at(1),
		m_pImg[7],
		fPoint((float)(pixelSize * 2), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 2);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[8]->at(0),
		m_pImg[8],
		fPoint(0, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 2);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[8]->at(1),
		m_pImg[8],
		fPoint((float)(pixelSize * 2), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 2);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[8]->at(2),
		m_pImg[8],
		fPoint((float)(pixelSize * 4), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 2);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[8]->at(3),
		m_pImg[8],
		fPoint((float)(pixelSize * 6), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 6);

	for (int i = 0; i < m_wAnimKey.size(); ++i)
	{
		if (1 == m_wAnimKey[i]->size())
		{
			UINT frameCount = (UINT)CResourceManager::getInst()->
				FindD2DImage(m_wImgKey[0])->GetWidth() / (UINT)pixelSize;
			GetAnimator()->CreateAnimation(
				m_wAnimKey[i]->at(0),
				m_pImg[i],
				fPoint(0.f, 0.f),
				fPoint(pixelSize, pixelSize),
				fPoint(pixelSize, 0.f), 0.1f, frameCount);
		}
	}
	GetAnimator()->Play(L"Fall0");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"Idle");
	pAni->GetFrame(0).fptOffset = fPoint(0.f, 5.f);
	pAni = GetAnimator()->FindAnimation(L"Down");
	pAni->GetFrame(0).fptOffset = fPoint(0.f, 5.f);

	// 중력
	CreateGravity();

	// 리지드바디 쓰자 충돌부분 보니까 써야겠다
	CreateRigidBody();
	CRigidBody* rigid = GetRigidBody();
	rigid->SetMaxSpeed(info.m_fMaxVelocity);

	// 상태
	CPlayerState* pAnim = new CPlayerAnim();
	CStateManager::getInst()->AddState(PLAYERSTATE::Anim, pAnim);
	CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::Anim);
	CPlayerState* pIdle = new CPlayerIdle();
	CStateManager::getInst()->AddState(PLAYERSTATE::IDLE, pIdle);
	CPlayerState* pMove = new CPlayerMove();
	CStateManager::getInst()->AddState(PLAYERSTATE::MOVE, pMove);
	CPlayerState* pAttack = new CPlayerAttack();
	CStateManager::getInst()->AddState(PLAYERSTATE::ATTACK, pAttack);
	CPlayerState* pJump = new CPlayerJump();
	CStateManager::getInst()->AddState(PLAYERSTATE::JUMP, pJump);
	CPlayerState* pFall = new CPlayerFall();
	CStateManager::getInst()->AddState(PLAYERSTATE::Fall, pFall);

	CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::IDLE);
	CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::Fall);

}

CPlayer::~CPlayer()
{
	for (int i = 0; i < m_wAnimKey.size(); ++i)
	{
		delete m_wAnimKey[i];
	}
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}


void CPlayer::update()
{
	if (KeyDown(VK_LEFT) || KeyDown(VK_RIGHT))
	{
		KeyDown(VK_RIGHT) ? m_bIsRight = true : m_bIsRight = false;
		//CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::MOVE);
	}
	if (KeyDown('C'))
	{
		//CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::ATTACK);
	}
	if (ANYKEYDOWN)
	{
		//CStateManager::getInst()->CommandSave();
	}
	if (KEYEMPTYDEFINE)
	{
		//CStateManager::getInst()->ChangeState(PLAYERSTATE::IDLE);
	}
	CStateManager::getInst()->update();
	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::SetIsGround(bool ground)
{
	m_bIsGround = ground;
}

void CPlayer::SetIsWall(bool wall, bool isright)
{
	m_bIsWall[0] = wall;
	m_bIsWall[1] = isright;
}

bool CPlayer::GetDir()
{
	return m_bIsRight;
}

bool CPlayer::GetIsGround()
{
	return m_bIsGround;
}

bool* CPlayer::GetIsWall()
{
	return m_bIsWall;
}



void CPlayer::SetCollisonCallBack(COLLIDER_FUNC pFunc, DWORD_PTR state)
{
	m_arrFunc.push_back(pFunc);
	m_colliderState = state;
}

void CPlayer::SetCollisonEnterCallBack(COLLIDER_FUNC pFunc, DWORD_PTR state)
{
	m_arrEnterFunc.push_back(pFunc);
	m_colliderEnterState = state;
}
void CPlayer::SetCollisonExitCallBack(COLLIDER_FUNC pFunc, DWORD_PTR state)
{
	m_arrExitFunc.push_back(pFunc);
	m_colliderExitState = state;
}

void CPlayer::OnCollision(CCollider* other)
{
	list<COLLIDER_FUNC>::iterator iter = m_arrFunc.begin();
	for (; iter != m_arrFunc.end(); ++iter)
	{
		COLLIDER_FUNC collFunc = *iter;
		collFunc(m_colliderState, other);
	}
}

void CPlayer::OnCollisionEnter(CCollider* other)
{
	CGameObject* pOtherObj = other->GetObj();
	if (pOtherObj->GetGroup() == GROUP_GAMEOBJ::TILE)
	{
		if (((CTile*)pOtherObj)->GetGroup() == GROUP_TILE::GROUND)
		{
			//++m_bIsGroundCount;
		}
	}
	list<COLLIDER_FUNC>::iterator iter = m_arrEnterFunc.begin();
	for (; iter != m_arrEnterFunc.end(); ++iter)
	{
		COLLIDER_FUNC collFunc = *iter;
		collFunc(m_colliderEnterState, other);
	}
}

void CPlayer::OnCollisionExit(CCollider* other)
{
	
	//CGameObject* pOtherObj = other->GetObj();
	//if (pOtherObj->GetGroup() == GROUP_GAMEOBJ::TILE)
	//{
	//	if (((CTile*)pOtherObj)->GetGroup() == GROUP_TILE::GROUND)
	//	{
	//		if (m_bIsGround)
	//		{
	//			if (!Key('X') && !Key('V'))
	//			{
	//				CStateManager::getInst()->ExitState(PLAYERSTATE::JUMP);
	//				CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::Fall);
	//			}
	//		}
	//		/*
	//		--m_bIsGroundCount;
	//		if (0 == m_bIsGroundCount)
	//		{
	//			if (!Key('X') && !Key('V'))
	//			{
	//				CStateManager::getInst()->ExitState(PLAYERSTATE::JUMP);
	//				CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::Fall);
	//			}
	//		}
	//		*/
	//	}
	//}

	list<COLLIDER_FUNC>::iterator iter = m_arrExitFunc.begin();
	for (; iter != m_arrExitFunc.end(); ++iter)
	{
		COLLIDER_FUNC collFunc = *iter;
		collFunc(m_colliderExitState, other);
	}
}