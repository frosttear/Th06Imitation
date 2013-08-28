//--------------------------------------------------------------------------------------
//File: Enemy.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "Enemy.h"
#include "GameManager.h"
#include "Bullet.h"

Enemy::Enemy(TextureType textureType,  int score, MotionInfo *pInfo, COLLISIONTYPE collisionType, const D3DXVECTOR2 &scaleMatrix, float rotation) 
	: GameObject(textureType, pInfo, collisionType, scaleMatrix, rotation)
{

	m_score				= score;
	m_hp				= 0;
	m_textureType		= textureType;
	m_shootInterval		= 10;//shootInerval;
	m_width				= 32;
	m_height			= 32;
	m_isInvincible		= false;
	m_shootFrame		= 0;
	m_startShootFrame	= 0;
	m_maxShootCount		= 0;
	m_shootLoopFrame	= 0;
	m_bonusItemType		= ITEM_TYPE_POINT;
	m_bIsDropBonus		= true;

}

void	Enemy::Shoot()
{
}

void	Enemy::Update()
{
	if (m_elapsedFrame > m_startShootFrame)
	{
		Shoot();
	}
	GameObject::Update();
	
}

void	Enemy::OnHit(GameObject * pObject)
{
	if (!m_isInvincible)
	{
		if (typeid(*pObject).name() == typeid(Player).name())
		{
			m_bIsValid = false;
		}else
		{
			
			m_hp -= ((Bullet*) pObject)->GetPower();
			if (m_hp <= 0)
			{	
				m_bIsValid = false;
				gm.AddScore(m_score);
			}
			
		}
	}
}

void	Enemy::OnWipped()
{
	m_bIsValid = false;
	gm.RemoveEnemy(this);
	if (IsInScreen() && m_bIsDropBonus)
	{
		gm.AddItem(&ItemFactory::GetItem(m_bonusItemType, this->GetCenter()));
	}
}