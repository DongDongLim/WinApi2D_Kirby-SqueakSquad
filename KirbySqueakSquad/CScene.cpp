#include "framework.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CTile.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CAnimObj.h"
#include "CMonster.h"

CScene::CScene()
{
    m_strName = L"";
}

CScene::~CScene()
{
    // ���� ���� ��� ���ӿ�����Ʈ ����
    for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; i++)
    {
        for (int j = 0; j < m_arrObj[i].size(); j++)
        {
            delete m_arrObj[i][j];
        }
    }
}

void CScene::update()
{
    // ���� ���� ��� ������Ʈ ������Ʈ
    for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; i++)
    {
        for (int j = 0; j < m_arrObj[i].size(); j++)
        {
            if (!m_arrObj[i][j]->isDead())
                m_arrObj[i][j]->update();
        }
    }
}

void CScene::finalupdate()
{
    // ���� ���� ��� ������Ʈ finalupdate
    for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; i++)
    {
        for (int j = 0; j < m_arrObj[i].size(); j++)
        {
            m_arrObj[i][j]->finalupdate();
        }
    }
}

void CScene::render()
{
    // ���� ���� ��� ������Ʈ render
    for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; i++)
    {
        if ((UINT)GROUP_GAMEOBJ::TILE == i)
        {
            render_tile();
            continue;
        }
        for (vector<CGameObject*>::iterator iter = m_arrObj[i].begin();
            iter != m_arrObj[i].end(); ++iter)
        {
            if (!(*iter)->isDead())
            {
                (*iter)->render();
            }
            /*
            else
            {
                iter = m_arrObj[i].erase(iter);
            }*/
        }
    }
}

void CScene::render_tile()
{
    const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
    for (UINT i = 0; i < vecTile.size(); i++)
    {
        vecTile[i]->render();
    }
}

const vector<CGameObject*>& CScene::GetGroupObject(GROUP_GAMEOBJ group)
{
    return m_arrObj[(UINT)group];
}

vector<CGameObject*>& CScene::GetUIGroup()
{
    return m_arrObj[(UINT)GROUP_GAMEOBJ::UI];
}

void CScene::SetName(const wstring& strName)
{
    m_strName = strName;
}

wstring CScene::GetName()
{
    return m_strName;
}

void CScene::AddObject(CGameObject* pObj, GROUP_GAMEOBJ type)
{
    pObj->SetGroup(type);
    m_arrObj[(int)type].push_back(pObj);
}

void CScene::DeleteGroup(GROUP_GAMEOBJ group)
{
    for (int i = 0; i < m_arrObj[(UINT)group].size(); i++)
    {
        delete m_arrObj[(UINT)group][i];
    }
    m_arrObj[(UINT)group].clear();
}

void CScene::DeleteAll()
{
    for (int i = 0; i < (UINT)GROUP_GAMEOBJ::SIZE; i++)
    {
        DeleteGroup((GROUP_GAMEOBJ)i);
    }
}

void CScene::LoadTile(const wstring& strPath)
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

    CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");

    for (UINT i = 0; i < tileCount; i++)
    {
        CTile* newTile = new CTile;
        newTile->Load(pFile);
        newTile->SetD2DImage(pImg);
        newTile->SetPos(fPoint((float)(newTile->GetX() * CTile::SIZE_TILE), (float)(newTile->GetY() * CTile::SIZE_TILE)));

        if (GROUP_TILE::SLOPE == newTile->GetGroup())
        {
            // TODO : OBB �浹ü �߰�
        }
        else if (GROUP_TILE::NONE != newTile->GetGroup())
        {
            newTile->CreateCollider();
            newTile->GetCollider()->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
            newTile->GetCollider()->SetOffsetPos(fPoint(CTile::SIZE_TILE / 2.f, CTile::SIZE_TILE / 2.f));
        }

        AddObject(newTile, GROUP_GAMEOBJ::TILE);
    }

    fclose(pFile);
}

void CScene::LoadAnim(const wstring& strPath, CGameObject* obj, CD2DImage* pImg)
{
    DeleteGroup(GROUP_GAMEOBJ::ANIMOBJ);

    FILE* pFile = nullptr;

    _wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
    assert(pFile);

    int iLen = (int)wcslen(strPath.c_str());
    wstring wFirst;

    wstring wSecond;

    for (int i = iLen - 1; i >= 0; i--)
    {
        if ('\\' == strPath.c_str()[i])
        {
            break;
        }
        wFirst += strPath.c_str()[i];
    }

    iLen = (int)wcslen(wFirst.c_str());

    for (int i = iLen - 1; i >= 0; i--)
    {
        if ('.' == wFirst.c_str()[i])
        {
            break;
        }
        wSecond += wFirst.c_str()[i];
    }

    UINT xCount = 0;
    UINT yCount = 0;
    UINT animCount = 0;

    fread(&xCount, sizeof(UINT), 1, pFile);
    fread(&yCount, sizeof(UINT), 1, pFile);
    fread(&animCount, sizeof(UINT), 1, pFile);

    CAnimator* animator = obj->GetAnimator();
    int nextSize = 0;
    1 == animCount ? nextSize = 0 : nextSize = CAnimObj::SIZE_ANIM;
    vector<CAnimObj*> vecAnim;
    for (UINT i = 0; i < animCount; ++i)
    {
        CAnimObj* newAnim = new CAnimObj;
        vecAnim.push_back(newAnim);
    }
    for (UINT i = 0; i < vecAnim.size(); ++i)
    {
        vecAnim[i]->Load(pFile);
    }
    if (obj->GetGroup() == GROUP_GAMEOBJ::MONSTER)
    {
        CMonster* mon = (CMonster*)obj;
        if (MON_TYPE::THROW == mon->GetType())
        {
            if (0 != nextSize)
                nextSize = (CAnimObj::SIZE_ANIM + 22);
            animator->CreateAnimation(wSecond, pImg,
                fPoint((vecAnim[0]->GetX() * (CAnimObj::SIZE_ANIM + 22))
                    , (vecAnim[0]->GetY() * (CAnimObj::SIZE_ANIM + 22)))
                , fPoint((CAnimObj::SIZE_ANIM + 22), (CAnimObj::SIZE_ANIM + 22))
                , fPoint(nextSize, 0.f)
                , vecAnim[0]->GetAccTime()
                , vecAnim.size());

        }
        else
        {
            animator->CreateAnimation(wSecond, pImg,
                fPoint((vecAnim[0]->GetX() * CAnimObj::SIZE_ANIM)
                    , (vecAnim[0]->GetY() * CAnimObj::SIZE_ANIM))
                , fPoint(CAnimObj::SIZE_ANIM, CAnimObj::SIZE_ANIM)
                , fPoint(nextSize, 0.f)
                , vecAnim[0]->GetAccTime()
                , vecAnim.size());
        }
    }
    else
    {
        animator->CreateAnimation(wSecond, pImg,
            fPoint((vecAnim[0]->GetX() * CAnimObj::SIZE_ANIM)
                , (vecAnim[0]->GetY() * CAnimObj::SIZE_ANIM))
            , fPoint(CAnimObj::SIZE_ANIM, CAnimObj::SIZE_ANIM)
            , fPoint(nextSize, 0.f)
            , vecAnim[0]->GetAccTime()
            , vecAnim.size());
    }
    CAnimation* pAni = animator->GetCreatenAnim();
    for (UINT i = 0; i < vecAnim.size(); ++i)
    {
        pAni->GetFrame(i).fptOffset = vecAnim[i]->GetOffSet();
        delete vecAnim[i];
    }
    fclose(pFile);
}
