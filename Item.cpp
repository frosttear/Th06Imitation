//--------------------------------------------------------------------------------------
//File: Item.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "Item.h"
#include "GameManager.h"
#include <vector>
Item::Item(const D3DXVECTOR2 &position) : GameObject(TEXTURE_BULLET1)
{
	m_position	  = position;
	m_score		= 10;
	m_power		= 0;
	m_life		= 0;
	m_bomb		= 0;
	m_collisionType = COLLISION_RECT;
}
//--------------------------------------------------------------------------------------
// Render Item , while out of screen, render the icon top of the screen
//--------------------------------------------------------------------------------------
void Item::Render(ID3DXSprite * pSprite)
{
	D3DXMATRIX transMatrix;
	RECT rect = m_pSprite->GetRect();
	if (m_position.y < ACTIVE_RECT_TOP - m_height) //item is out of screen ,show icon
	{
		if (rect.left < 128)
		{
			rect.left += 128;
			rect.right += 128;

			m_pSprite->Set(rect, 1, 0, m_width, m_height);
		}
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f, NULL, NULL, 0.0f, &D3DXVECTOR2(m_position.x, ACTIVE_RECT_TOP));
		
	}else
	{
		if (rect.left >= 128)
		{
			rect.left -= 128;
			rect.right -= 128;
			m_pSprite->Set(rect, 1, 0, m_width, m_height);			
		}
	
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f, NULL, NULL, 0.0f, &m_position);
	}

	pSprite->SetTransform(&transMatrix);
	m_pSprite->Render(pSprite, rm.GetTexture(m_textureType));
}
//--------------------------------------------------------------------------------------
//Update position,(at first should rise up, after a while should down.
//					if type is POINT, calculate current score)
//--------------------------------------------------------------------------------------
void Item::Update()
{
	AutoUpdatePosition();
	++m_elapsedFrame;
	if (m_position.y > ACTIVE_RECT_BOTTOM || (m_maxLifeTime > 0 && m_elapsedFrame > m_maxLifeTime))
	{
		m_bIsValid = false;
	}else
	{
		//const int MAX_POINT_LINE = 192;
		if (m_type == ITEM_TYPE_POINT && m_position.y > MAX_POINT_LINE)
		{
			m_score = ITEM_MAX_SCORE - ((int)m_position.y  - MAX_POINT_LINE) * 20;
		}
	}

}
//--------------------------------------------------------------------------------------
//While Wipped ,show score and play sound
//--------------------------------------------------------------------------------------
void Item::OnWipped()
{
	m_bIsValid = false;
	gm.RemoveItem(this);
	//show score if in screen
	if (IsInScreen())
	{
		std::vector<int> nums;
		int score = m_score;
		do
		{
			nums.push_back(score % 10);
			score /= 10;
			
		}
		while (score != 0);
		float startX  = m_position.x + m_width * 0.5f - nums.size() * 8 * 0.5f;
		for (int i = (int)nums.size() - 1; i >= 0; i --)
		{
			GameObject* pObject = new GameObject(TEXTURE_ASCII, 
				new MotionInfo(0, new LineTrack(D3DXVECTOR2(0,-1),1,0,0, D3DXVECTOR2(startX + 8 * (nums.size() - i - 1), m_position.y))));
			RECT srcRect;
			SetRect(&srcRect, 8 * nums[i], 0, 8 * nums[i] + 1, 8);
			//pObject->motionInfos.push_back(,D3DXVECTOR2())));
		//	pObject->motionIterator = pObject->motionInfos.begin();
			pObject->SetSprite(srcRect, 1, 0, 8, 8);
			pObject->SetMaxLifeTime(60);
			if (m_score == ITEM_MAX_SCORE || m_type == ITEM_TYPE_STAR )
				pObject->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
			gm.AddObject(pObject);
		}
	
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_ITEM));
	}

}

Item& ItemFactory::GetItem(ITEM_TYPE  type, const D3DXVECTOR2 &position)
{
	RECT rect;
	Item * pItem	= new Item(position);
	pItem->m_type	= type; 
	switch (type)
	{
		case ITEM_TYPE_POWER:
			pItem->m_power		= 1;
			SetRect(&rect, 0, 0 , 16 , 16);
			break;
		case ITEM_TYPE_POINT:
			pItem->m_score		= 10000;
			SetRect(&rect, 16, 0, 32 , 16);
			break;
		case ITEM_TYPE_BIGPOWER:
			pItem->m_power		= 8;
			SetRect(&rect, 32, 0, 48, 16);
			break;
		case ITEM_TYPE_BOMB:
			pItem->m_bomb = 1;
			SetRect(&rect, 48, 0, 64 , 16);
			break;
		case ITEM_TYPE_FULLPOWER:
			pItem->m_power		= 128;
			SetRect(&rect, 64, 0, 80, 16);
			break;
		case ITEM_TYPE_LIFE:
			pItem->m_life = 1;
			SetRect(&rect, 80, 0, 96, 16);
			break;
		case ITEM_TYPE_STAR:
			pItem->m_score			= ITEM_MAX_SCORE;
			SetRect(&rect, 96, 0, 112, 16);
			pItem->m_maxLifeTime	= 30;
			break;
	}
	pItem->SetSprite(rect, 1, 0, 16, 16);
	SetDefaultMotionInfos(pItem);
	return *pItem;
}

void	ItemFactory::SetDefaultMotionInfos(Item *pItem)
{
	if (pItem->m_type == ITEM_TYPE_STAR)
	{
		pItem->motionInfos.push_back(new MotionInfo(0, new StaticTrack(0, pItem->GetPosition())));
		pItem->motionIndex = 0;

	}else
	{
		pItem->motionInfos.push_back(new MotionInfo(0, new LineTrack(D3DXVECTOR2(0, -1), 3, 0, 0, pItem->GetPosition())));
		pItem->motionInfos.push_back(new MotionInfo(30, new LineTrack(D3DXVECTOR2(0, 1), 3, 0, 30, NULL_POSITION), true));
		pItem->motionIndex = 0;
	}
}