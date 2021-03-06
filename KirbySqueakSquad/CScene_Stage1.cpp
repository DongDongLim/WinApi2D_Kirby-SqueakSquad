#include "framework.h"
#include "CScene_Stage1.h"
#include "Map_Start.h"
#include "CPlayer.h"
#include "CMonster.h"
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
	// 타일 로딩
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\stage2Map.tile";
	LoadTile(path);

	vector<CGameObject*> arrObj = GetGroupObject(GROUP_GAMEOBJ::TILE);
	for (int i = 0; i < arrObj.size(); ++i)
	{
		CTile* tile = (CTile*)arrObj[i];
		tile->SetSlopePoint();
	}

	CMap* map = new CMap;
	map->Load(L"Map_Start", L"texture\\map\\stage2.png");
	AddObject(map, GROUP_GAMEOBJ::MAP);
	
	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Start", L"texture\\bg\\background1.png");
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	CPlayer* pPlayer = new CPlayer();
	pPlayer->SetPos(fPoint(50, 96));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	CMonster* pMon1 = CMonster::Create(MON_TYPE::CUTTER, fPoint(200.f, 128.5f));
	AddObject(pMon1, GROUP_GAMEOBJ::MONSTER);

	CMonster* pMon2 = CMonster::Create(MON_TYPE::THROW, fPoint(230.f, 63.5f));
	AddObject(pMon2, GROUP_GAMEOBJ::MONSTER);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MONSTER, GROUP_GAMEOBJ::TILE);
	// Camera Look 지정
	CCameraManager::getInst()->SetTargetObj(pPlayer);
	//CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

}

void CScene_Stage1::Exit()
{
	DeleteAll();
}
