//--------------------------------------------------------------------------------------
//File: Effect.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "Effect.h"
#include "GameSprite.h"
#include "GameManager.h"

//--------------------------------------------------------------------------------------
//EffectWhiteCircle
//--------------------------------------------------------------------------------------
EffectWhiteCircle::EffectWhiteCircle(const D3DXVECTOR2 &centerPosition) : GameObject(TEXTURE_EFF_00) 
{
	//m_position		= position
	m_maxLifeTime	= 20;
	RECT srcRect ;
	SetRect(&srcRect, 0, 192, 64, 256);
	SetSprite(srcRect, 1, 0, 64, 64);
	SetCenter(centerPosition);

}

void	EffectWhiteCircle::Render(ID3DXSprite * pSprite)
{
	pSprite->End();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	dxMgr.getD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	dxMgr.getD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);

	GameObject::Render(pSprite);
	//D3DXMATRIX transMatrix;
	//D3DXVECTOR2 centerVector(64 * 0.5f , 64 * 0.5f);
	//D3DXMatrixTransformation2D(&transMatrix, &centerVector, 0.0f,&m_scaleMatrix, NULL, 0.0f, &m_position);
	//pSprite->SetTransform(&transMatrix);
	//m_pSprite
	//pSprite->Draw(rm.GetTexture(TEXTURE_EFF_00), NULL, NULL, NULL, m_color);
	pSprite->End();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	
}

void	EffectWhiteCircle::Update(void)
{
	m_elapsedFrame ++;
	m_scaleMatrix.x += 0.3f;
	m_scaleMatrix.y += 0.3f;
//	int alpha = (m_maxLifeTime - m_elapsedFrame)  * 255 / m_maxLifeTime;
//	SetColor(alpha);
	if (m_elapsedFrame > m_maxLifeTime)
		m_bIsValid = false;
	
}
//--------------------------------------------------------------------------------------
//EffectEnemyDead
//--------------------------------------------------------------------------------------
EffectEnemyDead::EffectEnemyDead(const D3DXVECTOR2 & centerPosition) : GameObject(TEXTURE_EFF_00)
{
	m_maxLifeTime   = 15;
	RECT srcRect;
	SetRect(&srcRect,32, 0, 64, 32);
	//SetDirection(0, -1);
	SetSprite(srcRect, 1,0, 32, 32, false);
	SetCenter(centerPosition);

	//SetScaleMatrix(1.0f, 1.0f);
}

void EffectEnemyDead::Update(void)
{
	m_rotation = D3DXToRadian(18 * m_elapsedFrame);
	m_elapsedFrame ++;
	m_scaleMatrix.x += 0.1f;
	m_scaleMatrix.y += 0.1f;
	if (m_elapsedFrame > m_maxLifeTime)
		m_bIsValid = false;
	int alpha = (m_maxLifeTime - m_elapsedFrame ) * 255 / m_maxLifeTime;
	m_color	  = D3DCOLOR_ARGB(alpha, 255, 255, 255);

}

void EffectEnemyDead::Render(ID3DXSprite *pSprite)
{
//	D3DXMATRIX transMatrix;
//	D3DXVECTOR2 centerVector(m_width / 2.0f , m_height / 2.0f);
//	D3DXMatrixTransformation2D(&transMatrix, &centerVector, 0.0f,&m_scaleMatrix, &centerVector, m_rotation, &m_position);
	//pSprite->SetTransform(&transMatrix);
	pSprite->End();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//dxMgr.getD3DDevice()->SetRenderState(D3DRS_BLENDFACTOR, 
	dxMgr.getD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	dxMgr.getD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	GameObject::Render(pSprite);
//	m_pSprite->Render(pSprite, rm.GetTexture(m_textureType), m_color);
	pSprite->End();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}


EffectEnemyDead01::EffectEnemyDead01() : GameObject(TEXTURE_EFF_00)
{
	m_maxLifeTime   = 10;
	RECT srcRect;
	SetRect(&srcRect,0, 0, 32, 32);
	SetSprite(srcRect, 1,0, 32, 32, false);
}

void EffectEnemyDead01::Update()
{
	m_elapsedFrame ++;
	m_scaleMatrix.x += 0.1f;
	m_scaleMatrix.y += 0.1f;
	if (m_elapsedFrame > m_maxLifeTime)
		m_bIsValid = false;

}

void EffectEnemyDead01::Render(ID3DXSprite *pSprite)
{
	pSprite->End();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//int alpha = (m_maxLifeTime - m_elapsedFrame ) * 255 / m_maxLifeTime;
	//dxMgr.getD3DDevice()->SetRenderState(D3DRS_BLENDFACTOR, 
	dxMgr.getD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	dxMgr.getD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	GameObject::Render(pSprite);
	pSprite->End();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}
//--------------------------------------------------------------------------------------
//Class EffectBulletInit
//--------------------------------------------------------------------------------------
EffectBulletInit::EffectBulletInit(const D3DXVECTOR2 &centerPosition, RECT &srcRect)
				:GameObject(TEXTURE_BULLET1)
{
	m_maxLifeTime	= 30;
	SetSprite(srcRect, 1, 0, srcRect.right - srcRect.left, srcRect.bottom - srcRect.top);
	SetCenter(centerPosition);
	m_scaleMatrix.x = 1.5;
	m_scaleMatrix.y = 1.5;

}

void	EffectBulletInit::Render(ID3DXSprite * pSprite)
{
	GameObject::Render(pSprite);
}
void	EffectBulletInit::Update(void)
{
	m_color = D3DCOLOR_ARGB(255 - (int)(m_elapsedFrame * 1.0f / m_maxLifeTime * 255), 255, 255, 255);
	++m_elapsedFrame;
	if (m_elapsedFrame > m_maxLifeTime)
		m_bIsValid = false;

}

//TODO:Add EffectBulletHit,showed when player's bullet hit an enemy
EffectBulletHit::EffectBulletHit(const D3DXVECTOR2 &centerPosition)
						:GameObject(TEXTURE_EFF_00)
{
	RECT srcRect;
	SetRect(&srcRect,32, 0, 64, 32);
	SetSprite(srcRect, 1,0, 32, 32, false);
	SetCenter(centerPosition);
}

void	EffectBulletHit::Render(ID3DXSprite *pSprite)
{
}

void	EffectBulletHit::Update()
{
}

//EffectText : Render text at destRect
EffectText::EffectText(TextRender *pTextRender, const RECT &destRect, D3DCOLOR color)
:GameObject(TEXTURE_MUSICBG)
{
	m_pTextRender	= pTextRender;
	m_destRect		= destRect;
	m_color			= color;
	
}

void EffectText::Render(ID3DXSprite *pSprite)
{
	if (m_pTextRender != NULL)
	{
		
		m_pTextRender->render(dxMgr.getD3DDevice(), m_destRect, m_color);
	}
}

void EffectText::Update(void)
{
	GameObject::Update();
}
