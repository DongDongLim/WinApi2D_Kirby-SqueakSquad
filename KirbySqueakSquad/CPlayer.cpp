#include "framework.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CD2DImage.h"
#include "CState.h"
#include "CPlayerState.h"
#include "CTile.h"
#include "CGravity.h"
#include "CMonster.h"


CPlayer::CPlayer()
{
	//m_bIsGroundCount = 0;
	CStateManager::getInst()->SetPlayer(this);
	m_eAttackType = ATTACK_TYPE::NORMAL;
	m_colliderState = 0;
	m_colliderEnterState = 0;
	m_colliderExitState = 0;
	m_bIsRight = true;
	for (int i = 0; i < 8; ++i)
	{
		m_pGroundCollider[i] = nullptr;
	}

	SetName(L"Player");
	SetScale(fPoint(32.f, 32.f));

	// 콜라이더
	CreateCollider();
	GetCollider()->SetScale(fPoint(17.f, 17.f));
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
	m_wAnimKey[2]->push_back(L"WallImpact");
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
		m_wAnimKey[2]->at(2),
		m_pImg[2],
		fPoint((float)(pixelSize * 9), 0.f),
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
		fPoint((float)(pixelSize), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.05f, 4);

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
		fPoint(pixelSize, 0.f), 0.07f, 2);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[8]->at(2),
		m_pImg[8],
		fPoint((float)(pixelSize * 4), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.05f, 2);

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
			float time = 0.1f;
			if (i == 3)
				time = 0.01f;
			else if (i == 6)
				time = 0.05f;
			UINT frameCount = (UINT)CResourceManager::getInst()->
				FindD2DImage(m_wImgKey[i])->GetWidth() / (UINT)pixelSize;
			GetAnimator()->CreateAnimation(
				m_wAnimKey[i]->at(0),
				m_pImg[i],
				fPoint(0.f, 0.f),
				fPoint(pixelSize, pixelSize),
				fPoint(pixelSize, 0.f), time, frameCount);
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
	rigid->SetMass(1);

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
	CPlayerState* pFly = new CPlayerFly();
	CStateManager::getInst()->AddState(PLAYERSTATE::FLY, pFly);
	CPlayerState* pEat = new CPlayerEat();
	CStateManager::getInst()->AddState(PLAYERSTATE::EAT, pEat);
	CPlayerState* pDown = new CPlayerDown();
	CStateManager::getInst()->AddState(PLAYERSTATE::DOWN, pDown);

	CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::IDLE);
	CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::Fall);



	m_fWallLength = 0;
	m_fGroundLength = (GetCollider()->GetScale() / 2).Length()
		+ (fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE) / 2).Length();

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
		KeyDown(VK_LEFT) ? SetDir(false) : SetDir(true);
	}
	GroundCheck();
	CStateManager::getInst()->update();
	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
	CStateManager::getInst()->render();
	GroundCheckRender();
}

void CPlayer::GroundCheckRender()
{
	float fRealTimeLength;
	float fLengthX;
	float fLengthY;
	CCollider* m_pPlayerCollider = GetCollider();
	for (int i = 0; i < 8; ++i)
	{
		if (nullptr != m_pGroundCollider[i])
		{
			fLengthX = (m_pPlayerCollider->GetFinalPos() - m_pGroundCollider[i]->GetFinalPos()).x;
			fLengthY = (m_pPlayerCollider->GetFinalPos() - m_pGroundCollider[i]->GetFinalPos()).y;
			fRealTimeLength = fPoint(abs(fLengthX), abs(fLengthY)).Length();
			if (abs(fLengthX) > abs(fLengthY))
			{
				m_fGroundLength = fPoint(
					abs((m_pGroundCollider[i]->GetScale() / 2).x
						+ (m_pPlayerCollider->GetScale() / 2).x)
					, abs(fLengthY)).Length();
			}
			else
			{
				m_fGroundLength = fPoint(
					abs(fLengthX)
					, abs((m_pGroundCollider[i]->GetScale() / 2).y
						+ (m_pPlayerCollider->GetScale() / 2).y)).Length();
			}
			if (m_fGroundLength >= fRealTimeLength)
			{

				COLORREF rgb = RGB(0, 0, 0);
				rgb = RGB(255, 0, 255);

				fPoint fptRenderStartPos = CCameraManager::getInst()->GetRenderPos(m_pGroundCollider[i]->GetFinalPos());
				fPoint fptRenderFinalPos = CCameraManager::getInst()->GetRenderPos(m_pPlayerCollider->GetFinalPos());

				CRenderManager::getInst()->RenderLine(
					fptRenderStartPos,
					fptRenderFinalPos,
					rgb,
					2.f
				);
			}
		}
	}
}

PLAYERINFO& CPlayer::GetPlaeyrInfo()
{
	return info;
}



CCollider* CPlayer::GetGround()
{
	return *m_pGroundCollider;
}

void CPlayer::AddGroundCollider(CCollider* ground)
{
	bool istrue = false;
	for (int i = 0; i < 8; ++i)
	{
		if (nullptr != m_pGroundCollider[i])
		{
			if (m_pGroundCollider[i] == ground)
				istrue = true;
			break;
		}
	}
	if (!istrue)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (nullptr == m_pGroundCollider[i])
			{
				m_pGroundCollider[i] = ground;
				break;
			}
		}
	}
}

void CPlayer::GroundCheck()
{
	info.g_bIsDown = false;
	info.g_bIsUp = false;
	info.g_bIsRight = false;
	info.g_bIsLeft = false;

	fPoint fLeftUpPos = fPoint(-1, -1).normalize();
	fPoint fRightDownPos = fPoint(1, 1).normalize();
	float fRealTimeLength;
	float fLengthX;
	float fLengthY;
	CCollider* m_pPlayerCollider = GetCollider();
	float fDirX = GetRigidBody()->GetDir().x;
	float fDirY = GetRigidBody()->GetDir().y;

	// 지금 오브젝트 기준으로 생각했는데 플레이어 기준으로 생각해보자 굳이?
	/* TODO:
		지금은 정사각 콜라이더들을 기준으로 했기 때문에 기능이 돌아가지만
		직각사각형 콜라이더들이 부딫혔을때는 두 콜라이더를 이어주는 선이 둘과 겹치지 않을때
		각각의 가장 가까운 대각선을 기준으로 다시 설정해서 비교해주는 과정이 필요함
		현재 커비의 콜라이더는 정사각이므로 추가하지는 않았음
	*/
	for (int i = 0; i < 8; ++i)
	{
		if (nullptr != m_pGroundCollider[i])
		{
			fLengthX = (m_pPlayerCollider->GetFinalPos() - m_pGroundCollider[i]->GetFinalPos()).x;
			fLengthY = (m_pPlayerCollider->GetFinalPos() - m_pGroundCollider[i]->GetFinalPos()).y;
			fRealTimeLength = fPoint(abs(fLengthX), abs(fLengthY)).Length();
			if (abs(fLengthX) > abs(fLengthY))
			{
				m_fGroundLength = fPoint(
					abs((m_pGroundCollider[i]->GetScale() / 2).x
						+ (m_pPlayerCollider->GetScale() / 2).x)
					, abs(fLengthY)).Length();
			}
			else
			{
				m_fGroundLength = fPoint(
					abs(fLengthX)
					, abs((m_pGroundCollider[i]->GetScale() / 2).y
						+ (m_pPlayerCollider->GetScale() / 2).y)).Length();
			}

			if (m_fGroundLength >= fRealTimeLength)
			{
				fPoint fPlayerDisPos = fPoint(fLengthX, fLengthY).normalize();

				if (fPlayerDisPos.y <= fLeftUpPos.y)
				{
					if (fDirY > 0)
					{
						GetRigidBody()->SetVelocity(
							fPoint(GetRigidBody()->GetVelocity().x, 0));


						SetPos(fPoint(GetPos().x
							, (m_pGroundCollider[i]->GetFinalPos().y)
							- ((m_pPlayerCollider->GetOffsetPos().y)
								+ (m_pPlayerCollider->GetScale() / 2).y
								+ (m_pGroundCollider[i]->GetScale() / 2).y)));
					}
					info.g_bIsDown = true;
					GetGravity()->SetIsGround(true);
				}
				else if (fPlayerDisPos.y >= fRightDownPos.y)
				{
					if (fDirY < 0)
					{
						GetRigidBody()->SetVelocity(
							fPoint(GetRigidBody()->GetVelocity().x, 0));


						SetPos(fPoint(GetPos().x
							, (m_pGroundCollider[i]->GetFinalPos().y)
							+ ((m_pPlayerCollider->GetOffsetPos().y)
								+ (m_pPlayerCollider->GetScale() / 2).y
								+ (m_pGroundCollider[i]->GetScale() / 2).y)));
					}

					info.g_bIsUp = true;
				}
				else if (fPlayerDisPos.x < fLeftUpPos.x)
				{
					if (fDirX > 0)
					{
						GetRigidBody()->SetVelocity(
							fPoint(0, GetRigidBody()->GetVelocity().y));


						SetPos(fPoint(
							(m_pGroundCollider[i]->GetFinalPos().x)
							- ((m_pPlayerCollider->GetOffsetPos().x)
								+ (m_pPlayerCollider->GetScale() / 2).x
								+ (m_pGroundCollider[i]->GetScale() / 2).x)
							, GetPos().y));

					}

					info.g_bIsRight = true;
				}
				else if (fPlayerDisPos.x > fRightDownPos.x)
				{
					if (fDirX < 0)
					{
						GetRigidBody()->SetVelocity(
							fPoint(0, GetRigidBody()->GetVelocity().y));


						SetPos(fPoint(
							(m_pGroundCollider[i]->GetFinalPos().x)
							+ ((m_pPlayerCollider->GetOffsetPos().x)
								+ (m_pPlayerCollider->GetScale() / 2).x
								+ (m_pGroundCollider[i]->GetScale() / 2).x)
							, GetPos().y));

					}

					info.g_bIsLeft = true;
				}
			}
			else
			{
				m_pGroundCollider[i] = nullptr;
			}
		}
	}
	if (!info.g_bIsDown)
	{
		GetGravity()->SetIsGround(false);
	}
}


bool CPlayer::GetDir()
{
	return m_bIsRight;
}

void CPlayer::SetDir(bool dir)
{
	m_bIsRight = dir;
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

ATTACK_TYPE CPlayer::GetAttackType()
{
	return m_eAttackType;
}

void CPlayer::OnCollision(CCollider* other)
{
	if (other->GetObj()->GetGroup() == GROUP_GAMEOBJ::TILE)
	{
		CTile* tile = (CTile*)other->GetObj();
		if (tile->GetGroup() == GROUP_TILE::GROUND)
		{
			AddGroundCollider((CCollider*)other);
		}
	}

	list<COLLIDER_FUNC>::iterator iter = m_arrFunc.begin();
	for (; iter != m_arrFunc.end(); ++iter)
	{
		COLLIDER_FUNC collFunc = *iter;
		collFunc(m_colliderState, other);
	}
}

void CPlayer::OnCollisionEnter(CCollider* other)
{
	if (other->GetObj()->GetGroup() == GROUP_GAMEOBJ::MONSTER)
	{
		CMonster* mon = (CMonster*)other->GetObj();
		if (mon->GetIsEaten())
		{
			CStateManager::getInst()->LoadState(PLAYERSTATE::EAT);
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
	list<COLLIDER_FUNC>::iterator iter = m_arrExitFunc.begin();
	for (; iter != m_arrExitFunc.end(); ++iter)
	{
		COLLIDER_FUNC collFunc = *iter;
		collFunc(m_colliderExitState, other);
	}
}