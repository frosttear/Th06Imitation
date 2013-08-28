//--------------------------------------------------------------------------------------
//File: SelfBullet.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "SelfBullet.h"
#include "GameManager.h"
#include "Collision.h"

SelfBullet01::SelfBullet01(const D3DXVECTOR2 &position, float directionX, float directionY) 
			: Bullet(TEXTURE_PLAYER_00, 
					new MotionInfo(0, new LineTrack(D3DXVECTOR2(directionX, directionY), 10, 0, 0, position)), COLLISION_RECT, D3DXVECTOR2(1.5, 1.5))
{
	RECT srcRect;
	SetRect(&srcRect, 128, 0, 144, 16);
	SetSprite(srcRect, 1, 0, 16, 16);
//	m_v				= 10;
	m_power			= 2;
	m_bIsPlayer		= true;
	m_position		= position;
	SetColor(100);
//	motionInfos.push_back(new MotionInfo(0, new LineTrack(D3DXVECTOR2(directionX, directionY), 10, 0, 0, m_position)));
//	motionIterator = motionInfos.begin();

}
//--------------------------------------------------------------------------------------
//This bullet will rotate around itself
//--------------------------------------------------------------------------------------
//void SelfBullet01::Render(ID3DXSprite * pSprite)
//{
//
//
//	
//}
void SelfBullet01::Update()
{
	m_rotation = D3DXToRadian(15 * m_elapsedFrame);
	GameObject::Update();
}

void SelfBullet01::OnWipped()
{
	m_bIsValid = false;
	gm.RemoveBullet(this);
}

bool SelfBullet01::Collision(GameObject * pObject)
{
	return Collision::CollisionRect(&pObject->GetRect(), &this->GetRect());
}

SelfBullet02::SelfBullet02(const D3DXVECTOR2 &position, float directionX, float directionY) 
			: Bullet(TEXTURE_PLAYER_00, 
					new MotionInfo(0, new LineTrack(D3DXVECTOR2(directionX, directionY), 10, 0, 0, position)), COLLISION_RECT, D3DXVECTOR2(1.5, 1.5))
{
	m_position		= position;
	RECT srcRect;
	SetRect(&srcRect, 144, 0, 160, 16);
	SetSprite(srcRect, 1, 0, 16, 16);
	m_v				= 10;
	m_target		= NULL;
	m_power			= 1;
	m_bIsPlayer		= true;
	m_rotation		= D3DXToRadian(45);
	SetColor(100);
	
}
//--------------------------------------------------------------------------------------
//This bullet should track a valid enemy 
//--------------------------------------------------------------------------------------
void SelfBullet02::Update()
{
	if (m_elapsedFrame % 20 == 0)
	{
		Enemy * pEnemy	= gm.GetEnemy();
		if (pEnemy != NULL && m_target != (GameObject*)pEnemy)
		{
			m_target  = (GameObject*)pEnemy;
			motionInfos.push_back(new MotionInfo(m_elapsedFrame + 1, 
				new LineTrack(m_target->GetCenter() - this->GetCenter(), m_v, 0, m_elapsedFrame + 1, m_position)));
		}
	}
	GameObject::Update();

}

void SelfBullet02::OnWipped()
{
	m_bIsValid = false;
	gm.RemoveBullet(this);}

bool SelfBullet02::Collision(GameObject * pObject)
{
	return Collision::CollisionRect(&pObject->GetRect(), &this->GetRect());
}