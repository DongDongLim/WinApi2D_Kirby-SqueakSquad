#include "framework.h"
#include "CScene_Tool.h"
#include "CTile.h"
#include "resource.h"
#include "CScene.h"
#include "CTexture.h"
#include "commdlg.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CButtonUI.h"
#include "Map_Start.h"
#include "CTileButton.h"
#include "CD2DImage.h"
#include "CAnimation.h"
#include "CAnimObj.h"

INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CScene_Tool::CScene_Tool()
{
	m_pMap = nullptr;

	m_hWnd = 0;
	m_iIdx = 0;
	m_gTile = GROUP_TILE::NONE;
	m_gAnim = GROUP_ANIM::CHECK;
	m_velocity = 500;
	m_iTileX = 0;
	m_iTileY = 0;
	m_iAnimX = 0;
	m_iAnimY = 0;
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::STAGE_01);
	}

	if (Key('A'))
	{
		CCameraManager::getInst()->Scroll(fVec2(-1, 0),  m_velocity);
	}
	if (Key('D'))
	{
		CCameraManager::getInst()->Scroll(fVec2(1, 0), m_velocity);
	}
	if (Key('W'))
	{
		CCameraManager::getInst()->Scroll(fVec2(0, -1), m_velocity);
	}
	if (Key('S'))
	{
		CCameraManager::getInst()->Scroll(fVec2(0, 1), m_velocity);
	}

	SetAnimGroup();

	//SetTileIdx();
	//SetTileGroup();
}

void CScene_Tool::render()
{
	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
	for (UINT i = 0; i < vecTile.size(); i++)
	{
		vecTile[i]->render();
	}

	PrintMap();
	PrintAnimLine();
	PrintAnimGroup();
	//PrintTileLine();
	//PrintTileGroup();

	const vector<CGameObject*>& vecUI = GetGroupObject(GROUP_GAMEOBJ::UI);
	for (UINT i = 0; i < vecUI.size(); i++)
	{
		vecUI[i]->render();
	}
}


void CScene_Tool::Enter()
{

	m_hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILEBOX), hWnd, TileWinProc);
	ShowWindow(m_hWnd, SW_SHOW);

	//CreateTile(20, 20);
	//CreateTilePanel();
	CreateAnim(16, 10);

	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));


}

void CScene_Tool::Exit()
{
	EndDialog(m_hWnd, IDOK);
	DeleteAll();
}

void CScene_Tool::SetIdx(UINT idx)
{
	m_iIdx = idx;
}

void CScene_Tool::SetTileIdx()
{
	if (Key(VK_LBUTTON) || Key(VK_RBUTTON))
	{
		fPoint fptMousePos = MousePos();
		fptMousePos = CCameraManager::getInst()->GetRealPos(fptMousePos);

		int iTileX = m_iTileX;
		int iTileY = m_iTileY;

		int iCol = (int)fptMousePos.x / CTile::SIZE_TILE;
		int iRow = (int)fptMousePos.y / CTile::SIZE_TILE;

		if (fptMousePos.x < 0.f || iTileX <= iCol ||
			fptMousePos.y < 0.f || iTileY <= iRow)
		{
			return;		// ?????? ???? ???? ????
		}

		UINT iIdx = iRow * iTileX + iCol;
		const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
		if (Key(VK_LBUTTON))
			((CTile*)vecTile[iIdx])->SetImgIdx(m_iIdx);
		else if (Key(VK_RBUTTON))
			((CTile*)vecTile[iIdx])->SetImgIdx(0);
	}
}


void CScene_Tool::SetGroup(GROUP_TILE group)
{
	m_gTile = group;
}

void CScene_Tool::SetGroupAnim(GROUP_ANIM group)
{
	m_gAnim = group;
}

void CScene_Tool::SetTileGroup()
{
	if (Key(VK_LBUTTON) || Key(VK_RBUTTON))
	{
		fPoint fptMousePos = MousePos();
		fptMousePos = CCameraManager::getInst()->GetRealPos(fptMousePos);

		int iTileX = m_iTileX;
		int iTileY = m_iTileY;

		int iCol = (int)fptMousePos.x / CTile::SIZE_TILE;
		int iRow = (int)fptMousePos.y / CTile::SIZE_TILE;

		if (fptMousePos.x < 0.f || iTileX <= iCol ||
			fptMousePos.y < 0.f || iTileY <= iRow)
		{
			return;		// ?????? ???? ???? ????
		}

		UINT iIdx = iRow * iTileX + iCol;
		const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
		if (Key(VK_LBUTTON))
			((CTile*)vecTile[iIdx])->SetGroup(m_gTile);
		else if (Key(VK_RBUTTON))
			((CTile*)vecTile[iIdx])->SetGroup(GROUP_TILE::NONE);
	}
}

void CScene_Tool::SetAnimGroup()
{
	if (Key(VK_LBUTTON) || Key(VK_RBUTTON))
	{
		fPoint fptMousePos = MousePos();
		fptMousePos = CCameraManager::getInst()->GetRealPos(fptMousePos);

		int iAnimX = m_iAnimX;
		int iAnimY = m_iAnimY;

		int iCol = (int)fptMousePos.x / CAnimObj::SIZE_ANIM;
		int iRow = (int)fptMousePos.y / CAnimObj::SIZE_ANIM;

		if (fptMousePos.x < 0.f || iAnimX <= iCol ||
			fptMousePos.y < 0.f || iAnimY <= iRow)
		{
			return;		// ?????? ???? ???? ????
		}

		UINT iIdx = iRow * iAnimX + iCol;
		const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::ANIMOBJ);
		if (Key(VK_LBUTTON))
			((CAnimObj*)vecTile[iIdx])->SetGroupAnim(m_gAnim);
		else if (Key(VK_RBUTTON))
			((CAnimObj*)vecTile[iIdx])->SetGroupAnim(GROUP_ANIM::NONE);
	}
}

void CScene_Tool::SetAnimOffSet(fPoint offset)
{
	const vector<CGameObject*>& vecAnim = GetGroupObject(GROUP_GAMEOBJ::ANIMOBJ);
	for (UINT i = vecAnim.size() - 1; i >= 0; --i)
	{
		CAnimObj* pAnim = (CAnimObj*)vecAnim[i];
		if (GROUP_ANIM::NONE != pAnim->GetGroupAnim())
		{
			pAnim->SetOffSet(offset);
			break;
		}
	}
}

void CScene_Tool::SetAnimTime(float time)
{
	const vector<CGameObject*>& vecAnim = GetGroupObject(GROUP_GAMEOBJ::ANIMOBJ);
	for (UINT i = vecAnim.size() - 1; i >= 0; --i)
	{
		CAnimObj* pAnim = (CAnimObj*)vecAnim[i];
		if (GROUP_ANIM::NONE != pAnim->GetGroupAnim())
		{
			pAnim->SetAccTime(time);
			break;
		}
	}
}

void CScene_Tool::CreateTile(UINT xSize, UINT ySize)
{
	DeleteGroup(GROUP_GAMEOBJ::TILE);

	m_iTileX = xSize;
	m_iTileY = ySize;

	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"Tile", L"texture\\Tile\\tilemap.bmp");

	for (UINT y = 0; y < ySize; y++)
	{
		for (UINT x = 0; x < xSize; x++)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(fPoint((float)(x * CTile::SIZE_TILE), (float)(y * CTile::SIZE_TILE)));
			pTile->SetX(x);
			pTile->SetY(y);
			pTile->SetD2DImage(pImg);
			AddObject(pTile, GROUP_GAMEOBJ::TILE);
		}
	}
}

void CScene_Tool::CreateAnim(UINT xSize, UINT ySize)
{
	DeleteGroup(GROUP_GAMEOBJ::ANIMOBJ);

	m_iAnimX = xSize;
	m_iAnimY = ySize;


	for (UINT y = 0; y < ySize; y++)
	{
		for (UINT x = 0; x < xSize; x++)
		{
			CAnimObj* pAnim = new CAnimObj();
			pAnim->SetPos(fPoint((float)(x * CAnimObj::SIZE_ANIM), (float)(y * CAnimObj::SIZE_ANIM)));
			pAnim->SetX(x);
			pAnim->SetY(y);
			AddObject(pAnim, GROUP_GAMEOBJ::ANIMOBJ);
		}
	}
}

void CScene_Tool::SaveTile(const wstring& strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"wb");		// w : write, b : binary
	assert(pFile);

	UINT xCount = m_iTileX;
	UINT yCount = m_iTileY;
	UINT tileCount = 0;

	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		CTile* pTile = (CTile*)vecTile[i];
		if (0 != pTile->GetIdx() || GROUP_TILE::NONE != pTile->GetGroup())
			tileCount++;
	}

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	fwrite(&tileCount, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		CTile* pTile = (CTile*)vecTile[i];
		if (0 != pTile->GetIdx() || GROUP_TILE::NONE != pTile->GetGroup())
			((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CScene_Tool::SaveAnim(const wstring& strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"wb");		// w : write, b : binary
	assert(pFile);

	UINT xCount = m_iAnimX;
	UINT yCount = m_iAnimY;
	UINT animCount = 0;

	const vector<CGameObject*>& vecAnim = GetGroupObject(GROUP_GAMEOBJ::ANIMOBJ);

	for (UINT i = 0; i < vecAnim.size(); i++)
	{
		CAnimObj* pAnim = (CAnimObj*)vecAnim[i];
		if (GROUP_ANIM::NONE != pAnim->GetGroupAnim())
			animCount++;
	}

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	fwrite(&animCount, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < vecAnim.size(); i++)
	{
		CAnimObj* pAnim = (CAnimObj*)vecAnim[i];
		if (GROUP_ANIM::NONE != pAnim->GetGroupAnim())
			pAnim->Save(pFile);
	}

	fclose(pFile);
}

void CScene_Tool::LoadTile(const wstring& strPath)
{
	DeleteGroup(GROUP_GAMEOBJ::TILE);

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;
	UINT tileCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	fread(&tileCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"Tile", L"texture\\Tile\\tilemap.bmp");
	CTile* pTile = new CTile;

	for (UINT i = 0; i < tileCount; i++)
	{
		pTile->Load(pFile);
		UINT iIdx = pTile->GetY() * xCount + pTile->GetX();
		((CTile*)vecTile[iIdx])->SetX(pTile->GetX());
		((CTile*)vecTile[iIdx])->SetY(pTile->GetY());
		((CTile*)vecTile[iIdx])->SetImgIdx(pTile->GetIdx());
		((CTile*)vecTile[iIdx])->SetGroup(pTile->GetGroup());
	}

	fclose(pFile);
}

void CScene_Tool::LoadAnim(const wstring& strPath)
{
	DeleteGroup(GROUP_GAMEOBJ::ANIMOBJ);

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;
	UINT animCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	fread(&animCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CGameObject*>& vecAnim = GetGroupObject(GROUP_GAMEOBJ::ANIMOBJ);
	CAnimObj* pAnim = new CAnimObj;

	for (UINT i = 0; i < animCount; i++)
	{
		pAnim->Load(pFile);
		UINT iIdx = pAnim->GetY() * xCount + pAnim->GetX();
		((CAnimObj*)vecAnim[iIdx])->SetX(pAnim->GetX());
		((CAnimObj*)vecAnim[iIdx])->SetY(pAnim->GetY());
		((CAnimObj*)vecAnim[iIdx])->SetGroup(pAnim->GetGroup());
	}

	fclose(pFile);
}

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ?????? ??????.
	ofn.hwndOwner = hWnd;					// ???? ?????? ????.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ?????? ?????? ?????? ?????? ???? ????.
	ofn.nMaxFile = sizeof(szName); // lpstrFile?? ?????? ?????? ???? ??.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // ???? ????
	ofn.nFilterIndex = 0; // ???? ???? ????. 0?? all?? ???? ??????. ??????.
	ofn.lpstrFileTitle = nullptr; // ?????? ??
	ofn.nMaxFileTitle = 0; // ?????? ?? ?????? ????. nullptr???? 0.
	wstring strTileFolder = CPathManager::getInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // ????????. ?????? ???? ?????????? ??????, content->tile ?????? ??????.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ??????

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CScene_Tool::SaveAnimData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ?????? ??????.
	ofn.hwndOwner = hWnd;					// ???? ?????? ????.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ?????? ?????? ?????? ?????? ???? ????.
	ofn.nMaxFile = sizeof(szName); // lpstrFile?? ?????? ?????? ???? ??.
	ofn.lpstrFilter = L"ALL\0*.*\0Anim\0*.Anim"; // ???? ????
	ofn.nFilterIndex = 0; // ???? ???? ????. 0?? all?? ???? ??????. ??????.
	ofn.lpstrFileTitle = nullptr; // ?????? ??
	ofn.nMaxFileTitle = 0; // ?????? ?? ?????? ????. nullptr???? 0.
	wstring strAnimFolder = CPathManager::getInst()->GetContentPath();
	strAnimFolder += L"Anim";
	ofn.lpstrInitialDir = strAnimFolder.c_str(); // ????????. ?????? ???? ?????????? ??????, content->tile ?????? ??????.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ??????

	if (GetSaveFileName(&ofn))
	{
		SaveAnim(szName);
	}
}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ?????? ??????.
	ofn.hwndOwner = hWnd; // ???? ?????? ????.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ?????? ?????? ?????? ?????? ???? ????.
	ofn.nMaxFile = sizeof(szName); // lpstrFile?? ?????? ?????? ???? ??.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // ???? ????
	ofn.nFilterIndex = 0; // ???? ???? ????. 0?? all?? ???? ??????. ??????.
	ofn.lpstrFileTitle = nullptr; // ?????? ??
	ofn.nMaxFileTitle = 0; // ?????? ?? ?????? ????. nullptr???? 0.
	wstring strTileFolder = CPathManager::getInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // ????????. ?????? ???? ?????????? ??????, content->tile ?????? ??????.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ??????

	if (GetOpenFileName(&ofn))
	{
		LoadTile(szName);
	}
}

void CScene_Tool::LoadAnimData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ?????? ??????.
	ofn.hwndOwner = hWnd; // ???? ?????? ????.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ?????? ?????? ?????? ?????? ???? ????.
	ofn.nMaxFile = sizeof(szName); // lpstrFile?? ?????? ?????? ???? ??.
	ofn.lpstrFilter = L"ALL\0*.*\0Anim\0*.Anim"; // ???? ????
	ofn.nFilterIndex = 0; // ???? ???? ????. 0?? all?? ???? ??????. ??????.
	ofn.lpstrFileTitle = nullptr; // ?????? ??
	ofn.nMaxFileTitle = 0; // ?????? ?? ?????? ????. nullptr???? 0.
	wstring strAnimFolder = CPathManager::getInst()->GetContentPath();
	strAnimFolder += L"Anim";
	ofn.lpstrInitialDir = strAnimFolder.c_str(); // ????????. ?????? ???? ?????????? ??????, content->tile ?????? ??????.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ??????

	if (GetOpenFileName(&ofn))
	{
		LoadAnim(szName);
	}
}

void CScene_Tool::LoadMap()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ?????? ??????.
	ofn.hwndOwner = hWnd; // ???? ?????? ????.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ?????? ?????? ?????? ?????? ???? ????.
	ofn.nMaxFile = sizeof(szName); // lpstrFile?? ?????? ?????? ???? ??.
	ofn.lpstrFilter = L"ALL\0*.*\0Image\0*.png"; // ???? ????
	ofn.nFilterIndex = 0; // ???? ???? ????. 0?? all?? ???? ??????. ??????.
	ofn.lpstrFileTitle = nullptr; // ?????? ??
	ofn.nMaxFileTitle = 0; // ?????? ?? ?????? ????. nullptr???? 0.
	wstring strTileFolder = CPathManager::getInst()->GetContentPath();
	strTileFolder += L"map";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // ????????. ?????? ???? ?????????? ??????, content->tile ?????? ??????.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ??????

	if (GetOpenFileName(&ofn))
	{
		m_pMap = CResourceManager::getInst()->LoadToolD2DImage(szName);
	}
}

void ClickTileGroupButton(DWORD_PTR param1, DWORD_PTR param2)
{
	// param1 : Scene_tool
	// param2 : CButtonUI
	CScene_Tool* scene_tool = (CScene_Tool*)param1;
	CButtonUI* button = (CButtonUI*)param2;
	scene_tool->ClickTileGroup(button);
}
void CScene_Tool::ClickTileGroup(CButtonUI* button)
{
	if (m_gTile == GROUP_TILE::NONE)
	{
		m_gTile = GROUP_TILE::GROUND;
		button->SetText(L"Ground");
	}
	else if (m_gTile == GROUP_TILE::GROUND)
	{
		m_gTile = GROUP_TILE::WALL;
		button->SetText(L"WALL");
	}
	else if (m_gTile == GROUP_TILE::WALL)
	{
		m_gTile = GROUP_TILE::PLATFORM;
		button->SetText(L"PLATFORM");
	}
	else if (m_gTile == GROUP_TILE::PLATFORM)
	{
		m_gTile = GROUP_TILE::SLOPE;
		button->SetText(L"SLOPE");
	}
	else if (m_gTile == GROUP_TILE::SLOPE)
	{
		m_gTile = GROUP_TILE::GATE;
		button->SetText(L"GATE");
	}
	else if (m_gTile == GROUP_TILE::GATE)
	{
		m_gTile = GROUP_TILE::BREAK;
		button->SetText(L"BREAK");
	}
	else if (m_gTile == GROUP_TILE::BREAK)
	{
		m_gTile = GROUP_TILE::INSTUNTKILL;
		button->SetText(L"INSTUNTKILL");
	}
	else if (m_gTile == GROUP_TILE::INSTUNTKILL)
	{
		m_gTile = GROUP_TILE::LADDER;
		button->SetText(L"LADDER");
	}
	else if (m_gTile == GROUP_TILE::LADDER)
	{
		m_gTile = GROUP_TILE::NONE;
		button->SetText(L"NONE");
	}
}

void ClickTileButton(DWORD_PTR param1, DWORD_PTR param2)
{
	// param1 : Scene_tool
	// param2 : CTileButton
	CScene_Tool* scene_tool = (CScene_Tool*)param1;
	CTileButton* button = (CTileButton*)param2;
	scene_tool->ClickTile(button);
}

void CScene_Tool::ClickTile(CTileButton* button)
{
	SetIdx(button->GetIdx());
}

void CScene_Tool::CreateTilePanel()
{
	CPanelUI* panelTile = new CPanelUI;
	panelTile->SetName(L"panelTile");
	panelTile->SetScale(fPoint(400.f, 600.f));
	panelTile->SetPos(fPoint(WINSIZEX * 2.f - 450.f, 50.f));

	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");
	for (UINT y = 0; y < 12; y++)
	{
		for (UINT x = 0; x < 12; x++)
		{
			CTileButton* btnTile = new CTileButton;
			btnTile->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
			btnTile->SetPos(fPoint((float)x * CTile::SIZE_TILE + 50, (float)y * CTile::SIZE_TILE + 50));
			btnTile->SetPos(btnTile->GetPos() + fPoint(8.f, 8.f));
			btnTile->SetImage(pImg);
			btnTile->SetIdx(y * 12 + x);
			btnTile->SetClickedCallBack(ClickTileButton, (DWORD_PTR)this, (DWORD_PTR)btnTile);
			panelTile->AddChild(btnTile);
		}
	}

	CButtonUI* btnTileGroup = new CButtonUI;
	btnTileGroup->SetScale(fPoint(50.f, 50.f));
	btnTileGroup->SetPos(fPoint(0, 0));
	btnTileGroup->SetText(L"NONE");
	btnTileGroup->SetClickedCallBack(ClickTileGroupButton, (DWORD_PTR)this, (DWORD_PTR)btnTileGroup);
	panelTile->AddChild(btnTileGroup);

	AddObject(panelTile, GROUP_GAMEOBJ::UI);
}

void CScene_Tool::PrintMap()
{
	if (nullptr == m_pMap)
		return;

	fPoint pos = fPoint(0, 0);
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	CRenderManager::getInst()->RenderImage(
		m_pMap,
		pos.x,
		pos.y,
		pos.x + m_pMap->GetWidth(),
		pos.y + m_pMap->GetHeight()
	);
}

void CScene_Tool::PrintTileLine()
{
	fPoint pos = CCameraManager::getInst()->GetLookAt();
	pos = pos - (fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	// ?????? ????
	for (UINT y = 0; y <= m_iTileY; y++)
	{
		CRenderManager::getInst()->RenderLine(
			fPoint(0 - pos.x, y * CTile::SIZE_TILE - pos.y),
			fPoint(CTile::SIZE_TILE * m_iTileX - pos.x, y * CTile::SIZE_TILE - pos.y)
		);
	}

	// ?????? ????
	for (UINT x = 0; x <= m_iTileX; x++)
	{
		CRenderManager::getInst()->RenderLine(
			fPoint(x * CTile::SIZE_TILE - pos.x, 0 - pos.y),
			fPoint(x * CTile::SIZE_TILE - pos.x, CTile::SIZE_TILE * m_iTileY - pos.y)
		);
	}
}

void CScene_Tool::PrintAnimLine()
{
	fPoint pos = CCameraManager::getInst()->GetLookAt();
	pos = pos - (fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	// ?????? ????
	for (UINT y = 0; y <= m_iAnimY; y++)
	{
		CRenderManager::getInst()->RenderLine(
			fPoint(0 - pos.x, y * CAnimObj::SIZE_ANIM - pos.y),
			fPoint(CAnimObj::SIZE_ANIM * m_iAnimX - pos.x, y * CAnimObj::SIZE_ANIM - pos.y)
		);
	}

	// ?????? ????
	for (UINT x = 0; x <= m_iAnimX; x++)
	{
		CRenderManager::getInst()->RenderLine(
			fPoint(x * CAnimObj::SIZE_ANIM - pos.x, 0 - pos.y),
			fPoint(x * CAnimObj::SIZE_ANIM - pos.x, CAnimObj::SIZE_ANIM * m_iAnimY - pos.y)
		);
	}
}

void CScene_Tool::PrintTileGroup()
{
	fPoint pos = CCameraManager::getInst()->GetLookAt();
	pos = pos - fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);

	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
	CTile* pTile;

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		pTile = (CTile*)vecTile[i];
		if (GROUP_TILE::GROUND == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(255, 0, 0),
				3.f
			);
		}
		else if (GROUP_TILE::WALL == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(0, 255, 0),
				3.f
			);
		}
		else if (GROUP_TILE::PLATFORM == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(0, 0, 255),
				3.f
			);
		}
		else if (GROUP_TILE::SLOPE == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(255, 255, 0),
				3.f
			);
		}
		else if (GROUP_TILE::GATE == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(0, 255, 255),
				3.f
			);
		}
		else if (GROUP_TILE::BREAK == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(100, 100, 100),
				3.f
			);
		}
		else if (GROUP_TILE::INSTUNTKILL == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(255, 255, 255),
				3.f
			);
		}
		else if (GROUP_TILE::LADDER == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(0, 0, 0),
				3.f
			);
		}
	}
}

void CScene_Tool::PrintAnimGroup()
{
	fPoint pos = CCameraManager::getInst()->GetLookAt();
	pos = pos - fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);

	const vector<CGameObject*>& vecAnim = GetGroupObject(GROUP_GAMEOBJ::ANIMOBJ);
	CAnimObj* pAnim;

	for (UINT i = 0; i < vecAnim.size(); i++)
	{
		pAnim = (CAnimObj*)vecAnim[i];
		if (GROUP_ANIM::CHECK == pAnim->GetGroupAnim())
		{
			CRenderManager::getInst()->RenderEllipse(
				pAnim->GetPos().x + CAnimObj::SIZE_ANIM / 2.f - pos.x,
				pAnim->GetPos().y + CAnimObj::SIZE_ANIM / 2.f - pos.y,
				CAnimObj::SIZE_ANIM / 2.f,
				CAnimObj::SIZE_ANIM / 2.f,
				RGB(255, 0, 0),
				3.f
			);
		}
	}
}

// ???? ???? ?????? ?????? ????????????.
INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_SAVE)
		{
			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			//pToolScene->SaveTileData();
			pToolScene->SaveAnimData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_LOAD)
		{
			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			//pToolScene->LoadTileData();
			pToolScene->LoadAnimData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_MAP)
		{
			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadMap();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON_SIZE)
		{
			int x = GetDlgItemInt(hDlg, IDC_EDIT_SIZEX, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDIT_SIZEY, nullptr, false);

			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			/*pToolScene->DeleteGroup(GROUP_GAMEOBJ::TILE);
			pToolScene->CreateTile(x, y);*/
			pToolScene->DeleteGroup(GROUP_GAMEOBJ::ANIMOBJ);
			pToolScene->CreateAnim(x, y);
		}
		else if (LOWORD(wParam) == IDC_BUTTON_OFFSET)
		{
			int x = GetDlgItemInt(hDlg, IDC_EDIT_OFFSETX, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDIT_OFFSETY, nullptr, false);

			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->SetAnimOffSet(fPoint(x, y));
		}
		else if (LOWORD(wParam) == IDC_BUTTON_TIME)
		{
			int iTime = GetDlgItemInt(hDlg, IDC_EDIT_ACCTIME, nullptr, false);
			float time = (float)iTime / 100.f;
			

			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->SetAnimTime(time);
		}

		break;
	}
	return (INT_PTR)FALSE;
}