#include "framework.h"
#include "CScene_Stage1.h"
#include "Map_Start.h"
#include "CPlayer.h"
#include "CMap.h"
#include "CBackGround.h"


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
	CMap* map = new CMap;
	map->Load(L"Map_Start", L"texture\\map\\stage1.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);
	
	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Start", L"texture\\bg\\background.png");
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

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
