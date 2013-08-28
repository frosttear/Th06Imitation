//--------------------------------------------------------------------------------------
//File: Enemy.h
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include <string>
#include "GameObject.h"
#include "Item.h"
//Enemy Class: base class of enemy plane
class Enemy : public GameObject
{
public:
	//--------------------------------------------------------------------------------------
	//Initialize
	//--------------------------------------------------------------------------------------
//					Enemy() : GameObject()			{ m_isInvincible = false; m_hp = 0;}
					Enemy(TextureType textureType,  int score = 1000, MotionInfo *pInfo = NULL, 
								COLLISIONTYPE collisionType = COLLISION_RECT,const D3DXVECTOR2 &scaleMatrix = D3DXVECTOR2(1,1),
								float rotation = 0 );
	//--------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------
	virtual void	Shoot();
	virtual void	Update();
	virtual void	OnWipped();
	virtual void	OnHit(GameObject * object);
	//--------------------------------------------------------------------------------------
	//Getters and Setters
	//--------------------------------------------------------------------------------------
	bool			IsInvicible()					{ return m_isInvincible;}
	void			SetInvicible(bool flag)			{ m_isInvincible = flag;}
	void			SetCreateFrame(int frame)		{ m_createFrame = frame;}
	int				GetCreateFrame() const			{ return m_createFrame;}
	void			SetShootFrame(int frame)		{ m_shootFrame = frame;}
	void			SetBonusItemType(ITEM_TYPE type)		{ m_bonusItemType = type;}
	void			SetIsDropBonus(bool bIsDropBonus)		{ m_bIsDropBonus = bIsDropBonus;}
protected:
	int				m_hp;						//record enemy's current hp
	bool			m_isInvincible;				
	int				m_shootInterval;
	std::string		m_name;
	int				m_actionMode;
	int				m_score;
	int				m_createFrame;
	int				m_startShootFrame;			
	int				m_shootFrame;				//record how many frames have passed since current shoot began
	int				m_maxShootCount;
	int				m_shootLoopFrame;
	ITEM_TYPE		m_bonusItemType;
	bool			m_bIsDropBonus;
};