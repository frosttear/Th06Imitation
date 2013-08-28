//--------------------------------------------------------------------------------------
//File: Effect.h
//
//Desc: defines special effects like a white circle shows when objects disappear
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include "GameObject.h"
//--------------------------------------------------------------------------------------
//Class of special Effects
//--------------------------------------------------------------------------------------
class EffectWhiteCircle : public GameObject
{
public:
			EffectWhiteCircle(const D3DXVECTOR2 &centerPosition);
	void	Render(ID3DXSprite * pSprite);
	void	Update();
};

class EffectEnemyDead : public GameObject
{
public:
			EffectEnemyDead(const D3DXVECTOR2 &centerPosition);
	void	Render(ID3DXSprite * pSprite);
	void	Update();
};

class EffectEnemyDead01 : public GameObject
{
public:
			EffectEnemyDead01();
	void	Render(ID3DXSprite * pSprite);
	void	Update();
};

class EffectBulletInit : public GameObject
{
public:
			EffectBulletInit(const D3DXVECTOR2 &centerPosition, RECT &srcRect);
	void	Render(ID3DXSprite * pSprite);
	void	Update(void);
};

class EffectBulletHit : public GameObject
{
public:
			EffectBulletHit(const D3DXVECTOR2 &centerPosition);
	void	Render(ID3DXSprite *pSprite);
	void	Update(void);
};

class EffectText : public GameObject
{
public:
			EffectText(TextRender *pTextRender, const RECT &destRect, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void	Render(ID3DXSprite *pSprite);
	void	Update(void);
	void	SetText(LPCSTR text){ m_pTextRender->SetText(text);}
	void	SetColor(D3DCOLOR color) { m_color = color;}
	void	SetDestRect(RECT &rect) { m_destRect = rect;}
private:
	TextRender*		m_pTextRender;
	RECT			m_destRect;
	D3DCOLOR		m_color;
};