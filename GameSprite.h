//--------------------------------------------------------------------------------------
//File: GameSprite.h
//
//Desc: encapsulate the sprite that auto render certain frames as an animation
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include <d3dx9.h>
#include <string>
//--------------------------------------------------------------------------------------
// Class GameSprite
// Render itself
//--------------------------------------------------------------------------------------
class GameSprite
{
public:
								GameSprite(RECT &srcRect,int numFrames, int frameInterval,
								int width, int height, bool bLoop = true);
	void						Set(RECT &srcRect,int numFrames, int frameInterval,
								int width, int height, bool bLoop = true);
	RECT						GetRect(){ return m_srcRect;}
	void						Render(ID3DXSprite * pSprite,LPDIRECT3DTEXTURE9 pTexture , D3DCOLOR color = D3DCOLOR_ARGB(255,255,255,255));
	void						SetAutoRenderFrame(int startFrame, int endFrame, int frameInterval, bool bLoop = true);

protected:

	RECT						m_srcRect;				// the texture source rect
	int							m_numFrames;			// number of frames this animation has
	int							m_frameInterval;		// the interval to change frame
	int							m_startFrame;			// the start frame for auto render
	int							m_endFrame;				// the end frame for atuo render
	int							m_frameWidth;			// frame width 
	int							m_frameHeight;			// frame height 
	bool						m_bLoop;
	unsigned int				m_elapsedFrame;
};