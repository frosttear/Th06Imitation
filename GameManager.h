//--------------------------------------------------------------------------------------
//File: GameManager.h
//
//Desc: GameManager Class, used to Control the whole game
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#pragma warning(disable: 4996)
#include <list>
#include <d3dx9.h>
#include "./dxutil/diKeyboardManager.h"
#include "./dxutil/TextRender.h"
#include "GameConstants.h"
#include "ResourceManager.h"
//--------------------------------------------------------------------------------------
//Game State Flag
//--------------------------------------------------------------------------------------
#define GAME_STATE_INIT			0x0001
#define GAME_STATE_PAUSE		0x0002
#define GAME_STATE_RUN			0x0003
#define	GAME_STATE_OPTION		0x0004
#define GAME_STATE_END			0x0005
#define GAME_STATE_TITLE		0x0006
#define GAME_STATE_STAGE_CLEAR  0x0007
#define GAME_STATE_CHAT			0x0008
//--------------------------------------------------------------------------------------
//Screen constance
//--------------------------------------------------------------------------------------
#define	SCR_WIDTH				640
#define	SCR_HEIGHT				512
#define MAX_STAGE_NUM			2
//--------------------------------------------------------------------------------------
//Forward declaration
//--------------------------------------------------------------------------------------
class GameObject;
class Player;
class GameSprite;
class Bullet;
class Item;
class Enemy;
  
class GameManager
{
public:
	static	GameManager&		GetInstance() { static GameManager gm; return gm;}
							    ~GameManager();
	void						Update();
	void						Render();
	
	//--------------------------------------------------------------------------------------
	//Render Number , render number by pics
	//--------------------------------------------------------------------------------------
	void						RenderNumber(const int number,const int count,  D3DXVECTOR2 * pPosition, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255), TextureType textureType = TEXTURE_ASCII); 
	void						RenderAsciiText(std::string text,  D3DXVECTOR2 * pPosition, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255), TextureType textureType = TEXTURE_ASCII);
	DWORD						GetGameState(){ return m_state;}
	void						SetGameState(DWORD state) { m_state = state;}
	void						SetBackground(LPDIRECT3DTEXTURE9 pTexture){m_background = pTexture;}
	LPDIRECT3DTEXTURE9			GetBackground() const					 {return m_background;}
	//--------------------------------------------------------------------------------------
	//Vectors : Objects, Bullets, Items, And Enemies
	//--------------------------------------------------------------------------------------
	void						AddBullet(Bullet *pBullet){m_objects.push_back((GameObject*)pBullet); m_bullets.push_back(pBullet);}
	void						RemoveBullet(Bullet *pBullet);
	void						AddItem(Item *pItem){ m_objects.push_back((GameObject*)pItem);m_items.push_back(pItem);}
	void						RemoveItem(Item *pItem);
	void						AddEnemy(Enemy *pEnemy){m_objects.push_back((GameObject*)pEnemy);m_enemies.push_back(pEnemy);}
	void						RemoveEnemy(Enemy *pEnemy);
	void						AddObject(GameObject *pObject) {m_objects.push_back(pObject);}
	Item*						GetItem(){  if (!m_items.empty()) return *(m_items.begin()); else return NULL;}
	Enemy*						GetEnemy();
	Player*						GetPlayer(){return m_pPlayer;}
	void						ClearBullets(void);
	void						ChangeBulletsToStars(void);
	
	void						AddScore(int delta){ m_score += delta; if (m_score < 0) m_score = 0;}
	int							GetDifficulty() const { return m_difficulty;}
	void						OnStageClear();
	LPDIRECT3DTEXTURE9			GetBackgroundOfStage(int stage);
	LPDIRECTSOUNDBUFFER			GetBGMOfStage(int stage);
	int							GetCurrentStage(){ return m_stage;}
	void						InitStage(int stage);
	void						ChangeBGM(LPDIRECTSOUNDBUFFER pBuffer);

private:
//--------------------------------------------------------------------------------------
//	Private Funcs
//--------------------------------------------------------------------------------------
								GameManager();
	DWORD						GameStateRun();
	DWORD						GameStatePause();
	DWORD						GameStateInit();
	DWORD						GameStateTitle();
	DWORD						GameStateStageClear();
	DWORD						GameStateEnd();
	DWORD						GameStateChat();
	void						RenderFront();
	void						RenderBattleScene();
	void						RenderTitle();
	void						RenderPauseMenu();
	void						RenderBackground();
	void						RenderStageClear();
	void						RenderChatDialog();
	void						Collision();
	void						DeleteAllObjects(void);
	void						ChangeState(DWORD state);
//--------------------------------------------------------------------------------------
//	Member Variables
//--------------------------------------------------------------------------------------
	std::list<GameObject* >		m_objects;
	std::list<Enemy *>			m_enemies;
	std::list<Bullet*>			m_bullets;		//stores all valid bullets
	std::list<Item*>			m_items;
	std::list<TextRender*>		m_texts;
	DWORD						m_state;		//flag to show current state
	int							m_stage;		//current stage;
	int							m_selectedIndex;		//
	Player *					m_pPlayer;				//
	unsigned int				m_stateElapsedFrame;
	unsigned int				m_score;
	unsigned int				m_highestScore;
	int							m_difficulty;
	LARGE_INTEGER				timeStart;
	LARGE_INTEGER				timeEnd;
	LARGE_INTEGER				timerFreq;
	float						m_anim_rate;
	LPDIRECTSOUNDBUFFER			m_bgmBuffer;
	LPDIRECT3DTEXTURE9			m_background;
	
	std::string					m_chatText;
	TextRender *				m_pTextRender;
	
};
static GameManager&	gm			=  GameManager::GetInstance(); 

