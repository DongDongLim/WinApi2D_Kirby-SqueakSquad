#include "framework.h"
#include "CTile.h"
#include "CD2DImage.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CPlayerState.h"
#include "CScene.h"

CTile::CTile()
{
	m_pImg = nullptr;
	m_iX = 0;
	m_iY = 0;
	m_iIdx = 0;
	m_group = GROUP_TILE::NONE;
	m_fLeftPos = fPoint(0, 0);
	m_fRightPos = fPoint(0, 0);
	SetScale(fPoint(SIZE_TILE, SIZE_TILE));
}

CTile::~CTile()
{
}

CTile* CTile::Clone()
{
	return new CTile(*this);
}

void CTile::update()
{
}

void CTile::render()
{
	if (nullptr == m_pImg)
	{
		return;
	}

	UINT iWidth = m_pImg->GetWidth();
	UINT iHeight = m_pImg->GetHeight();

	UINT iMaxRow = iHeight / SIZE_TILE;
	UINT iMaxCol = iWidth / SIZE_TILE;

	UINT iCurRow = (m_iIdx / iMaxCol) % iMaxRow;
	UINT iCurCol = (m_iIdx % iMaxCol);

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos());
	fPoint fptScale = GetScale();

	if (0 != m_iIdx)
	{
		CRenderManager::getInst()->RenderFrame(
			m_pImg,
			fptRenderPos.x,
			fptRenderPos.y,
			fptRenderPos.x + fptScale.x,
			fptRenderPos.y + fptScale.y,
			iCurCol * fptScale.x,
			iCurRow * fptScale.y,
			(iCurCol + 1) * fptScale.x,
			(iCurRow + 1) * fptScale.y
		);
	}
	if (GROUP_TILE::SLOPE == m_group)
	{
		fPoint startPos = CCameraManager::getInst()->GetRenderPos(m_fLeftPos);
		fPoint endPos = CCameraManager::getInst()->GetRenderPos(m_fRightPos);
		CRenderManager::getInst()->RenderLine(
			startPos,
			endPos,
			RGB(100, 255, 100),
			2.f
		);
	}


	component_render();
}

void CTile::SetD2DImage(CD2DImage* pImg)
{
	m_pImg = pImg;
}

void CTile::SetImgIdx(UINT idx)
{
	m_iIdx = idx;
}

void CTile::SetX(int x)
{
	m_iX = x;
}

void CTile::SetY(int y)
{
	m_iY = y;
}

void CTile::SetGroup(GROUP_TILE group)
{
	m_group = group;
}

void CTile::SetSlopePoint()
{
	/* TODO : 씬이나 타일메니저 만들어서 하나에서 처리하도록 지금은 각 타일에서 타일을 모두 검사해 연산 낭비가 있음
	*/
	if (GROUP_TILE::SLOPE == m_group)
	{
		bool istrue = false;
		vector<CGameObject*> m_arrObj = CSceneManager::getInst()->GetCurScene()->GetGroupObject(GROUP_GAMEOBJ::TILE);
		for (int i = m_arrObj.size() - 1; i >= 0; --i)
		{
			CTile* tile = (CTile*)m_arrObj[i];

			if (((int)tile->GetPos().x == ((int)GetPos().x - SIZE_TILE)
				&& (int)tile->GetPos().y == (int)GetPos().y) && GROUP_TILE::SLOPE != tile->GetGroup())
			{
				m_fLeftPos = fPoint(GetPos().x, GetPos().y);
				m_fRightPos = fPoint(GetPos().x + SIZE_TILE, GetPos().y + SIZE_TILE / 2);
				istrue = true;
				break;
			}
		}
		if (!istrue)
		{
			for (int i = m_arrObj.size() - 1; i >= 0; --i)
			{
				CTile* tile = (CTile*)m_arrObj[i];

				if (((int)tile->GetPos().x == ((int)GetPos().x + SIZE_TILE)
					&& (int)tile->GetPos().y == (int)GetPos().y) && GROUP_TILE::SLOPE != tile->GetGroup())
				{
					m_fLeftPos = fPoint(GetPos().x, GetPos().y + SIZE_TILE / 2);
					m_fRightPos = fPoint(GetPos().x + SIZE_TILE, GetPos().y);
					istrue = true;
					break;
				}
			}
			if (!istrue)
			{
				for (int i = m_arrObj.size() - 1; i >= 0; --i)
				{
					CTile* tile = (CTile*)m_arrObj[i];

					if (((int)tile->GetPos().x == (int)GetPos().x - SIZE_TILE)
						&& ((int)tile->GetPos().y == (int)GetPos().y + SIZE_TILE))
					{
						m_fLeftPos = fPoint(GetPos().x, GetPos().y + SIZE_TILE);
						m_fRightPos = fPoint(GetPos().x + SIZE_TILE, GetPos().y + SIZE_TILE / 2);
						istrue = true;
						break;
					}
				}
				if (!istrue)
				{
					for (int i = m_arrObj.size() - 1; i >= 0; --i)
					{
						CTile* tile = (CTile*)m_arrObj[i];
						if ((int)tile->GetPos().x == ((int)GetPos().x + SIZE_TILE)
							&& (int)tile->GetPos().y == ((int)GetPos().y + SIZE_TILE))
						{
							m_fLeftPos = fPoint(GetPos().x, GetPos().y + SIZE_TILE / 2);
							m_fRightPos = fPoint(GetPos().x + SIZE_TILE, GetPos().y + SIZE_TILE);
							istrue = true;
							break;
						}
					}

				}

			}
		}
	}
}

int CTile::GetIdx()
{
	return m_iIdx;
}

int CTile::GetX()
{
	return m_iX;
}

int CTile::GetY()
{
	return m_iY;
}

GROUP_TILE CTile::GetGroup()
{
	return m_group;
}

fPoint CTile::GetSlopeLeftPos()
{
	return m_fLeftPos;
}

fPoint CTile::GetSlopeRightPos()
{
	return m_fRightPos;
}


void CTile::Save(FILE* pFile)
{
	fwrite(&m_iX, sizeof(int), 1, pFile);
	fwrite(&m_iY, sizeof(int), 1, pFile);
	fwrite(&m_iIdx, sizeof(int), 1, pFile);

	int group = (int)m_group;
	fwrite(&group, sizeof(int), 1, pFile);
}

void CTile::Load(FILE* pFile)
{
	fread(&m_iX, sizeof(int), 1, pFile);
	fread(&m_iY, sizeof(int), 1, pFile);
	fread(&m_iIdx, sizeof(int), 1, pFile);

	int group;
	fread(&group, sizeof(int), 1, pFile);
	m_group = (GROUP_TILE)group;
}
