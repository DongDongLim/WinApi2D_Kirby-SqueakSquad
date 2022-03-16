#include "framework.h"
#include "CScene_Stage1.h"
#include "Map_Start.h"
#include "CPlayer.h"


CScene_Stage1::CScene_Stage1()
{
}

CScene_Stage1::~CScene_Stage1()
{
}

void CScene_Stage1::update()
{
	CScene::update();
}

void CScene_Stage1::Enter()
{
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	Map_Start* pDefaltMap = new Map_Start();
	pDefaltMap->SetScale(fPoint(528, 256));
	pDefaltMap->SetPos(fPoint(0, 0));
	AddObject(pDefaltMap, GROUP_GAMEOBJ::TILEBG);

	CPlayer* pPlayer = new CPlayer();
	pPlayer->SetPos(fPoint(0, 0));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	
	// Camera Look ÁöÁ¤
	CCameraManager::getInst()->SetTargetObj(pPlayer);
	
}

void CScene_Stage1::Exit()
{
	DeleteAll();
}
