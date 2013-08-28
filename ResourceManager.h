//--------------------------------------------------------------------------------------    
//File		:  ResourceManager.h
//Path		:  D:\MYPROJECTS\TH06-LIKE\TH06-LIKE\
//Author    :  Liu.zhenxing
//CreateTime:  2010/9/15 9:01
//Desc		:  Encapsulates Textures,Sound and BGM resources.Offers Load and Get operation
//--------------------------------------------------------------------------------------
#pragma once
#ifndef RESOURCE_MANAGE_H
#define RESOURCE_MANAGE_H

#include "./dxutil/dxManager.h"
#include "./dxutil/dsManager.h"
#include "GameConstants.h"

class ResourceManager
{
public:
	static	ResourceManager&	GetInstance() { static ResourceManager rm; return rm;}
								~ResourceManager(void);
	void						LoadResource(void);
	LPDIRECT3DTEXTURE9			GetTexture(TextureType type)  const	{if (m_bIsReady) return m_pTextures[type]; else return NULL;}
	LPDIRECTSOUNDBUFFER			GetSoundBuffer(SoundType type)const {if (m_bIsReady) return m_soundBuffers[type]; else return NULL;}
	LPDIRECTSOUNDBUFFER			GetBGMBuffer(BGMType	type) const {if (m_bIsReady) return m_bgmBuffers[type]; else return NULL;}
	RECT						GetRectOfAscii(char ch);
	RECT						GetRectOfDigit(int);
private:
								ResourceManager(void);
	void						LoadTexture(void);
	void						LoadSound(void);

	LPDIRECTSOUNDBUFFER			m_soundBuffers[SOUND_NUM];
	LPDIRECTSOUNDBUFFER			m_bgmBuffers[BGM_NUM];
	LPDIRECT3DTEXTURE9			m_pTextures[TEXTURE_NUM];
	bool						m_bIsReady;
};
static ResourceManager&	rm		=  ResourceManager::GetInstance(); 
#endif