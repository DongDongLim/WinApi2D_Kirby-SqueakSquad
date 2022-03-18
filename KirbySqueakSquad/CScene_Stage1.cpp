#include "framework.h"
#include "CScene_Stage1.h"
#include "Map_Start.h"
#include "CPlayer.h"
#include "CMap.h"
#include "CBackGround.h"
#include "CStateManager.h"


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
	// Ÿ�� �ε�
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\stage1Map.tile";
	LoadTile(path);

	CMap* map = new CMap;
	map->Load(L"Map_Start", L"texture\\map\\stage1.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);
	
	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Start", L"texture\\bg\\background1.png");
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	CPlayer* pPlayer = new CPlayer();
	pPlayer->SetPos(fPoint(50, 130));
	CStateManager::getInst()->SetPlayer(pPlayer);
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	
	// Camera Look ����
	CCameraManager::getInst()->SetTargetObj(pPlayer);
	//CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / g_winScale / 2.f, WINSIZEY / g_winScale / 2.f));
}

void CScene_Stage1::Exit()
{
	DeleteAll();
}
