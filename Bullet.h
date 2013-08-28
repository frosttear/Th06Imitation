//--------------------------------------------------------------------------------------
//File: Bullet.h
//
//Desc: declares bullet classes
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include <d3dx9math.h>
#include "GameObject.h"
enum BULLET_SHAPE{
	BULLET_SHAPE_LASER = 1,
	BULLET_SHAPE_CIRCLE,
	BULLET_SHAPE_SOLIDCIRCLE,
	BULLET_SHAPE_DIAMOND,
	BULLET_SHAPE_LITTLE_KNIFE,
	BULLET_SHAPE_3D_DIAMOND,
	BULLET_SHAPE_LIGHT_CIRCLE,
	BULLET_SHAPE_KNIFE,
	BULLET_SHAPE_FLAME,
	BULLET_SHAPE_LITTLE_CIRCLE,
//	BULLET_TYPE_
};
//enum BULLET_COLOR{
//	BULLET_COLOR_WHITE,
//	BULLET_COLOR_RED,
//	BULLET_COLOR_PURPLE,
//	BULLET_COLOR_BLUE,
//	BULLET_COLOR_LIGHT_BLUE,
//	BULLET_COLOR_GREEN,
//	BULLET_COLOR_YELLOW,
//};

//--------------------------------------------------------------------------------------
//Class Bullet: base class of bullets
//--------------------------------------------------------------------------------------
class Bullet : public GameObject
{
public:
							Bullet(TextureType textureType = TEXTURE_BULLET1, MotionInfo * pInfo = NULL, COLLISIONTYPE collisionType = COLLISION_RECT, 
										const D3DXVECTOR2 &scaleMatrix = D3DXVECTOR2(1,1), float rotation = 0);
	virtual void			Update(void);
	virtual void			Render(ID3DXSprite* pSprite);
	virtual void			OnWipped();
	virtual bool			Collision(GameObject * pObject);
	int						GetPower(void){return m_power;}
	bool					IsPlayer(void){return m_bIsPlayer;}
	void					SetSrcRect(RECT &rect) { m_srcRect	= rect;}
	void					SetInitRect(RECT &rect){ m_initRect = rect;}
	void					SetWippedRect(RECT &rect){ m_wippedRect = rect;}
	void					SetOwner(GameObject* pOwner){ m_pOwner = pOwner;}
	GameObject*				GetOwner() const			{ return m_pOwner;}
	void					SetIsGrazed(bool bIsGrazed)	{ m_bIsGrazed = bIsGrazed;}
	bool					IsGrazed() const { return m_bIsGrazed;}
protected:
	int						m_power;
	bool					m_bIsPlayer;
	bool					m_bIsGrazed;
	RECT					m_srcRect;
	RECT					m_wippedRect;
	RECT					m_initRect;
	GameObject*				m_pOwner;
};	