// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#pragma comment(lib, "Msimg32.lib")

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <math.h>
#include <assert.h>

// STL
#include <vector>
#include <map>
#include <list>

using namespace std;

// Util
#include "SingleTon.h"
#include "struct.h"
#include "Logger.h"


//========================================
//## 게임 그룹						##
//========================================

enum class GROUP_GAMEOBJ
{
	DEFAULT,
	BACKGROUND,
	MAP,
	TILE,
	TILEBG,
	PLAYER,
	MONSTER,
	MISSILE_PLAYER,
	MISSILE_MONSTER,
	ANIMOBJ,

	UI,		// UI는 모든 게임오브젝트 중 최상단 Layer에 위치
	SIZE,
};

enum class GROUP_SCENE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	SIZE,
};

enum class GROUP_TILE
{
	NONE,
	GROUND,
	PLATFORM,
	WALL,
	SLOPE,
	GATE,
	BREAK,
	INSTUNTKILL,
	LADDER,

	SIZE,
};

enum class GROUP_ANIM
{
	CHECK,

	NONE,
};

enum class STATE_MON
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,
	INHALE,
	DAMAGED,

	SIZE,
};

//========================================
//## 이벤트 타입					##
//========================================

enum class TYPE_EVENT
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_SCENE,
	CHANGE_AI_STATE,
	CHANGE_STATE_PLAYER,

	SIZE,
};

//========================================
//## 상태 타입					##
//========================================


enum class PLAYERSTATE
{
	Anim,
	IDLE,
	MOVE,
	DOWN,
	JUMP,
	Fall,
	FLY,
	EAT,
	TRANSFORM,
	ATTACK,

	END,
};

enum class COMMANDKEY
{
	DASH,
	CHANGEDIR,
	TURNOFF,

	END
};

// Core & Manager
#include "CCore.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CCollisionManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"
#include "CSoundManager.h"
#include "CRenderManager.h"

//========================================
//##			디파인문				##
//========================================

#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	256
#define	WINSIZEY	192
#define WINSTYLE	WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

#define DT				CTimeManager::getInst()->GetDT()
#define fDT				CTimeManager::getInst()->GetfDT()

#define Key(key)		CKeyManager::getInst()->GetButton(key)
#define KeyUp(key)		CKeyManager::getInst()->GetButtonUP(key)
#define KeyDown(key)	CKeyManager::getInst()->GetButtonDOWN(key)

#define MousePos()		CKeyManager::getInst()->GetMousePos()

#define CreateObj(pObj, group)	CEventManager::getInst()->EventCreateObject(pObj, group)
#define DeleteObj(pObj)			CEventManager::getInst()->EventDeleteObject(pObj)
#define ChangeScn(scene)		CEventManager::getInst()->EventChangeScene(scene)
#define ChangeAIState(ai, state)	CEventManager::getInst()->EventChangeAIState(ai, state)
#define ZOOM				CCameraManager::getInst()->GetZoom()

//========================================
//## 전역변수(인스턴스, 윈도우 핸들)	##
//========================================

extern HINSTANCE hInst;
extern HWND hWnd;

// TODO : 윈도우 메뉴를 통해 사이즈 배율 조절
