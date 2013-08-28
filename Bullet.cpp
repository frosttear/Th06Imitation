//--------------------------------------------------------------------------------------
//File: Bullet.cpp
//
//Desc: defines  Initialize, Set and OnWipped() of Bullets
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "Bullet.h"
#include "GameManager.h"
#include "Player.h"
#include "Collision.h"
#include "Effect.h"

Bullet::Bullet(TextureType textureType, MotionInfo * pInfo, COLLISIONTYPE collisionType, const D3DXVECTOR2 &scaleMatrix, float rotation)
		:GameObject(textureType, pInfo, collisionType, scaleMatrix, rotation)
{
	m_bIsPlayer		= false;
	m_power			= 0;
	m_bIsGrazed		= false;
}
//pObject is Player 
bool Bullet::Collision(GameObject * pObject)
{
	switch (m_collisionType)
	{
	case COLLISION_CIRCLE:
		return Collision::CollisionCircle(((CollisionCircle *)m_pCollisionInfo)->radius, &GetCenter(),
										((CollisionCircle *)pObject->GetCollisionInfo())->radius, &pObject->GetCenter());
	case COLLISION_RECT:
		return Collision::CollisionCircleRect(&GetRect(), ((CollisionCircle *)pObject->GetCollisionInfo())->radius, &pObject->GetCenter());
	//TODO: Add COLLISION_TRIANGLE 
	//case COLLISION_TRIANGLE:
	//	D3DXVECTOR2 p1;
	//	D3DXVECTOR2 p2;
	//	D3DXVECTOR2 p3;
	default:
		return false;
	}
}

void Bullet::Update(void)
{
	if (m_elapsedFrame == 0)
	{
		SetSprite(m_srcRect, 1, 0, m_srcRect.right - m_srcRect.left, m_srcRect.bottom - m_srcRect.top);
	}else
	{
		if (m_elapsedFrame == 1)
		{
			gm.AddObject(new EffectBulletInit(GetCenter(), m_initRect));
		}
	}
	GameObject::Update();
	
}
void Bullet::Render(ID3DXSprite * pSprite)
{
	GameObject::Render(pSprite);
}
void Bullet::OnWipped()
{
	m_bIsValid = false;
	gm.RemoveBullet(this);
	GameObject *pObj = new GameObject(TEXTURE_BULLET1);
	pObj->SetSprite(m_wippedRect, 1, 0, m_wippedRect.right - m_wippedRect.left, m_wippedRect.bottom - m_wippedRect.top);
	pObj->SetCenter(this->GetCenter());
	pObj->SetMaxLifeTime(15);
	gm.AddObject(pObj);
	
}