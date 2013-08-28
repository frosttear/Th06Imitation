//--------------------------------------------------------------------------------------
//File: Player.h
//
//Desc: describes the player's actions and data
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once

#include "GameObject.h"



#define PLAYER_STATE_LEFT			0x01
#define PLAYER_STATE_RIGHT			0x02
#define	PLAYER_STATE_NORMAL			0x03
#define MAX_POWER  128

#define	  PLAYER_START_POS_X		((ACTIVE_RECT_RIGHT - ACTIVE_RECT_LEFT) / 2 + ACTIVE_RECT_LEFT)
#define	  PLAYER_START_POS_Y		(ACTIVE_RECT_BOTTOM - 100)
#define	  PLAYER_DEAD_TIME			60

//class GameObject;
class GameSprite;
class Bullet;
class Player	:		public GameObject
{
public:
//--------------------------------------------------------------------------------------
//	Contructor & Destructor
//--------------------------------------------------------------------------------------
						Player();
						~Player();
	void				Init();
	bool				Create(float v, float lowV, int lifeNum = 3, int bombNum = 3 ,float radius = 2.0f);
//--------------------------------------------------------------------------------------
// Event functions
//--------------------------------------------------------------------------------------
	void				OnKeyPressed();
	void				Shoot();
	void				Bomb();
	void				OnWipped();
	void				OnGrazed();
	void				Render(ID3DXSprite * pSprite);
	void				RenderDead();
	void				Update();
//--------------------------------------------------------------------------------------
//	Setter & Getter
//--------------------------------------------------------------------------------------
	int					GetLifeNum(){return m_lifeNum;}
	void				AddLifeNum(int delta);
	int					GetBombNum(){return m_bombNum;}
	void				AddBomb(int delta);
	int					GetPower() {return m_power;}
	int					GetPowerLevel();
	void				PowerUp(int delta);
	int					GetGrazeNum() {return m_grazeNum;}
	int					GetPointNum() {return m_pointNum;}
	void				SetLowSpeedMode(bool flag) { m_bLowSpeedMode = flag;}
	bool				IsLowSpeedMode() { return m_bLowSpeedMode;}
	void				SetState(DWORD);
	bool				IsInvincible(){return m_isInvincible;}
	float				GetCollisionRadius(){return m_collisionRadius;}
	float				GetGrazeRadius(){return m_grazeRadius;}
	void				AddPointNum(int delta){m_pointNum += delta; if (m_pointNum < 0) m_pointNum = 0; }
protected:
	//player params
	int					m_lifeNum;				//remain life num
	int					m_bombNum;				//remain bomb num
	int					m_power;
	int					m_grazeNum;
	int					m_pointNum;
//--------------------------------------------------------------------------------------
//move stuff
//--------------------------------------------------------------------------------------
	GameSprite	*		m_pSprite;
	GameSprite	*		m_pBallSprite;
	Bullet		*		m_pPrimaryBullet;
	Bullet		*		m_pSecondaryBullet;

	D3DXVECTOR2			m_ballPosition;
	float				m_lowV;
	bool				m_isInvincible;
	bool				m_bLowSpeedMode;		//flag of speed mode
	DWORD				m_state;
	unsigned int		m_shootFrame;
	unsigned int		m_bombFrame;

	float				m_collisionRadius;
	float				m_grazeRadius;
};