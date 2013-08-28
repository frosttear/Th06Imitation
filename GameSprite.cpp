//--------------------------------------------------------------------------------------
//File: GameSprite.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include ".\GameSprite.h"
using namespace std;
//--------------------------------------------------------------------------------------
// GameSprite : used to render the GameObjects 
//--------------------------------------------------------------------------------------
GameSprite::GameSprite(RECT &srcRect, int numFrames, int frameInterval, 
					   int width, int height, bool bLoop)
{
	
	Set(srcRect,numFrames, frameInterval, width, height, bLoop);

}

void	GameSprite::Set(RECT &srcRect,int numFrames, int frameInterval,
								int width, int height, bool bLoop)
	{
		m_srcRect			= srcRect;
		m_numFrames		    = numFrames;
		m_frameInterval		= frameInterval;	
		m_startFrame		= 0;
		m_endFrame			= numFrames - 1 > 0 ? numFrames - 1 : 0;
		m_frameWidth		= width;
		m_frameHeight		= height;
		m_bLoop				= bLoop;
		m_elapsedFrame		= 0;
	}

void	GameSprite::SetAutoRenderFrame(int startFrame, int endFrame, int frameInterval,  bool bLoop)
{
	m_startFrame	= startFrame;
	m_endFrame		= endFrame;
	m_frameInterval = frameInterval;
	m_bLoop			=  bLoop;
	m_elapsedFrame	= 0;
}
//--------------------------------------------------------------------------------------
// render from startFrame to end frame by frames
// TODO:Modify elapsedFrame to in param instead of member variable
//--------------------------------------------------------------------------------------
void	GameSprite::Render(ID3DXSprite * pSprite, LPDIRECT3DTEXTURE9 pTexture , D3DCOLOR color)
{
	int curFrame = m_startFrame;//shows which frames should be render now
	if (m_startFrame != m_endFrame)
	{
		int frameStep	= m_elapsedFrame / m_frameInterval;
		if (m_startFrame > m_endFrame)
		{
			if (m_bLoop)
			{
				
				frameStep  =  frameStep % (m_startFrame - m_endFrame + 1);
			}
			else
			{
				if (frameStep > m_startFrame - m_endFrame)
					frameStep = m_startFrame - m_endFrame;
			}
			curFrame -=  frameStep;
		
		}else
		{
			if (m_bLoop)
			{
				frameStep  =  frameStep % (m_endFrame - m_startFrame   + 1);
			}else
			{
				if (frameStep > m_endFrame - m_startFrame)
					frameStep = m_endFrame - m_startFrame;
			}
			curFrame +=  frameStep;
		}
	}
	RECT frameSrcRect;
	frameSrcRect.top  = m_srcRect.top + curFrame * m_frameWidth / (m_srcRect.right - m_srcRect.left) * m_frameHeight;
	frameSrcRect.left = m_srcRect.left + curFrame  * m_frameWidth %  (m_srcRect.right - m_srcRect.left);
	frameSrcRect.bottom = frameSrcRect.top + m_frameHeight;
	frameSrcRect.right = frameSrcRect.left + m_frameWidth;

	pSprite->Draw(pTexture, &frameSrcRect, NULL, NULL, color);
	m_elapsedFrame ++;

}

