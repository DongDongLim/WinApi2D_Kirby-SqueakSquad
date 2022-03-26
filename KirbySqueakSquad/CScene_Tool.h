#pragma once
#include "CScene.h"

class CD2DImage;
class CButtonUI;
class CTileButton;

class CScene_Tool : public CScene
{
private:
	CD2DImage* m_pMap;

	HWND m_hWnd;
	UINT m_iIdx;
	GROUP_TILE m_gTile;
	GROUP_ANIM m_gAnim;
	float m_velocity;

	UINT m_iTileX;
	UINT m_iTileY;

	UINT m_iAnimX;
	UINT m_iAnimY;

public:
	CScene_Tool();
	~CScene_Tool();

	virtual void update();
	virtual void render();

	virtual void Enter();
	virtual void Exit();

	void SetIdx(UINT idx);
	void SetTileIdx();		// ���콺�� ��ȣ�ۿ��ؼ� Ÿ���� �ٲ�.
	void SetGroup(GROUP_TILE group);
	void SetGroupAnim(GROUP_ANIM group);
	void SetTileGroup();
	void SetAnimGroup();
	void SetAnimOffSet(fPoint offset);
	void SetAnimTime(float time);

	void CreateTile(UINT xSize, UINT ySize);
	void CreateAnim(UINT xSize, UINT ySize);
	void SaveTile(const wstring& strPath);
	void SaveAnim(const wstring& strPath);
	void LoadTile(const wstring& strPath);
	void LoadAnim(const wstring& strPath);
	void SaveTileData();
	void SaveAnimData();
	void LoadTileData();
	void LoadAnimData();
	void LoadMap();

	void ClickTileGroup(CButtonUI* button);
	void ClickTile(CTileButton* button);

private:
	void CreateTilePanel();

	void PrintMap();
	void PrintTileLine();
	void PrintAnimLine();
	void PrintTileGroup();
	void PrintAnimGroup();


};

