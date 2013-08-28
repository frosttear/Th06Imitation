//--------------------------------------------------------------------------------------
//File: Player.cpp
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------

#include "GameManager.h"
#include "GameSprite.h"
#include "Player.h"
#include "Effect.h"
#include "SelfBullet.h"
#include "Item.h"

using namespace std;

Player::Player () : GameObject(TEXTURE_PLAYER_00)
{
	m_grazeNum			= 0;
	m_pointNum			= 0;
	m_lifeNum			= 2;
	m_power				= 0;
//	m_textureType		= ;
	m_v					= 4;
	m_lowV				= 2;
	m_width				= 32;
	m_height			= 48;
	m_collisionRadius	= 2.0f;
	m_grazeRadius		= 8.0f;
	m_pCollisionInfo    = new CollisionCircle(m_collisionRadius);
	RECT srcRect;
	SetRect(&srcRect, 0, 0, 128, 48);
	m_pSprite = new GameSprite(srcRect, 4, 8, m_width, m_height);
	SetRect(&srcRect, 128, 16, 144, 32);
	m_pBallSprite = new GameSprite(srcRect,1, 8,  16, 16);
	Init();
}
bool Player::Create(float v,float lowV, int lifeNum, int bombNum, float radius)
{
	m_v					= v;
	m_lowV				= lowV;
//	m_intersectRadius	= radius;
	m_bombNum			= bombNum;
	m_lifeNum			= lifeNum;
	return true;
}

void Player::Init()
{
	m_bombNum		= 3;
	m_shootFrame	= 0;
	m_bombFrame		= 0;
	m_bLowSpeedMode = false;
	SetState(PLAYER_STATE_NORMAL);
	m_isInvincible  = true;
	m_bIsValid		= true;
	m_position.x	= PLAYER_START_POS_X;
	m_position.y	= PLAYER_START_POS_Y;

}
Player::~Player()
{
	SAFE_DELETE (m_pSprite);
	SAFE_DELETE (m_pBallSprite);
}

void Player::Shoot()
{
	//shoot primary bullet
	int interval = (int)(6 * (1 - m_power / 512.0f)) ;
	if (m_shootFrame % interval == 0)
	{
		D3DXVECTOR2 startPos(m_position.x + 8, m_position.y + m_height / 2); 
		switch (GetPowerLevel())
		{
			case 0 :
			case 1 :
		
				gm.AddBullet(new SelfBullet01(startPos, 0, -1));
				break;
			case 2 :
				
				gm.AddBullet(new SelfBullet01(startPos,  -1 , -20));
				gm.AddBullet(new SelfBullet01(startPos, 1 , -20));
				break;
			case 3 :
				gm.AddBullet(new SelfBullet01(startPos, -1 , -8));
				gm.AddBullet(new SelfBullet01(startPos, 0, -1));
				gm.AddBullet(new SelfBullet01(startPos, 1, -8));
				break;
			case 4 :
				gm.AddBullet(new SelfBullet01(startPos,  -1 , -8));
				gm.AddBullet(new SelfBullet01(startPos,  -1, -20));
				gm.AddBullet(new SelfBullet01(startPos,  1, -20));
				gm.AddBullet(new SelfBullet01(startPos,  1, -8));
				
		}
		
	}
	//shoot secondary bullet
	interval = (int)(12 * (1 - m_power / 512.0f)) ;
	if (m_shootFrame % interval == 0)
	{
		D3DXVECTOR2 startPos(m_ballPosition.x - 8, m_ballPosition.y); 
		D3DXVECTOR2 startPosRight((m_position.x + m_width / 2 - m_ballPosition.x ) * 2 + m_ballPosition.x - 16, m_ballPosition.y);

		if (m_power >= 8 )
		{
			if (m_power < 64)
			{	
				gm.AddBullet(new SelfBullet02(startPos,  -1, -2));
				gm.AddBullet(new SelfBullet02(startPosRight,  1, -2));

			}else
			{
				gm.AddBullet(new SelfBullet02(startPos,  -1, -1));
				gm.AddBullet(new SelfBullet02(startPos,  -1, -2));
				gm.AddBullet(new SelfBullet02(startPosRight, 1, -1));
				gm.AddBullet(new SelfBullet02(startPosRight, 1, -2));
			}
		}
	}
	
}

//
//TODO: complete bomb
//
void Player::Bomb()
{
	if (m_bombFrame >0)
	{
		return;
	}
}
//--------------------------------------------------------------------------------------
//if state changes, reset player's sprite, to render proper actions 
//--------------------------------------------------------------------------------------
void	Player::SetState(DWORD state)
{
	
	if (m_state != state)
	{
		RECT srcRect;
		//m_elapsedFrame = 0;
		switch(state)
		{
			case	PLAYER_STATE_NORMAL:
				SetRect(&srcRect, 0, 0, 128, 48);
				m_pSprite->Set(srcRect, 4, 8, 32, 48);
				m_pSprite->SetAutoRenderFrame(0, 3,8);
				break;
			case	PLAYER_STATE_LEFT:
			case	PLAYER_STATE_RIGHT:
				SetRect(&srcRect, 0, 48, 224, 96);
				m_pSprite->Set(srcRect, 7, 8, 32, 48);
				m_pSprite->SetAutoRenderFrame(0, 6, 4 , false);
				break;

		}
	
		m_state = state;
	}
}

void Player::OnKeyPressed()
{
	m_bLowSpeedMode = diMgr.isKeyDown (DIK_LSHIFT);
	
	float x = 0;
	float y = 0;
	int state = PLAYER_STATE_NORMAL;
	//--------------------------------------------------------------------------------------
	// Set direction according to the input
	//--------------------------------------------------------------------------------------
	if (diMgr.isKeyDown(DIK_UP) && m_position.y > ACTIVE_RECT_TOP )
		y = -1;
	if (diMgr.isKeyDown(DIK_DOWN) && m_position.y < ACTIVE_RECT_BOTTOM - m_height)
		y = 1;
	if (diMgr.isKeyDown (DIK_LEFT))
	{
		state = PLAYER_STATE_LEFT;
		if (m_position.x  > ACTIVE_RECT_LEFT)
			x = -1;
	}
	
	if (diMgr.isKeyDown (DIK_RIGHT)) 
	{
		state = PLAYER_STATE_RIGHT;
		if (m_position.x < ACTIVE_RECT_RIGHT - m_width)
			x = 1;
	}
	SetDirection(x, y);
	SetState(state); 
	//--------------------------------------------------------------------------------------
	//Check Shoot and Bomb input 
	//--------------------------------------------------------------------------------------
	if (diMgr.isKeyDown (DIK_Z) || (m_shootFrame > 0 && m_shootFrame < 60 ))
	{

		rm.GetSoundBuffer(SOUND_PLST)->SetVolume(- 1500);
		dsMgr.playSoundLoop( rm.GetSoundBuffer(SOUND_PLST));
		Shoot();
		m_shootFrame ++;
	}
	else
	{	
		dsMgr.stopSound( rm.GetSoundBuffer(SOUND_PLST));
		m_shootFrame = 0;
	}
	
	if (diMgr.isKeyDown (DIK_X)) 
		Bomb();
	


}
//--------------------------------------------------------------------------------------
// update
// update position and state according to input
//--------------------------------------------------------------------------------------
void Player::Update()
{

	if (!m_bIsValid)
	{
		if (m_elapsedFrame > PLAYER_DEAD_TIME)
		{
			Init();
		}
		else
		{
			gm.ClearBullets();
		}
	}
	m_elapsedFrame ++;
	
	/*if (m_elapsedFrame > 30 && m_bombFrame == 0)
		m_isInvincible = false;*/
	if (!m_bIsValid)
		return;
	OnKeyPressed();
	//Update position
	float speed	= m_bLowSpeedMode ? m_lowV : m_v;
	m_position.x += speed * m_direction.x;
	m_position.y += speed * m_direction.y;
	m_ballPosition.x += speed * m_direction.x;
	m_ballPosition.y += speed * m_direction.y;
	//the ball will move to the head if shift pressed ,deal with the animate
	if (m_bLowSpeedMode)
	{
		if	(m_ballPosition.x < m_position.x)
		{
			m_ballPosition.x += 2;
			m_ballPosition.y -= 4;
		}
	}else
	{
		m_ballPosition.x	= m_position.x - 20 ;
		m_ballPosition.y	= m_position.y + 20;
	}
}
void Player::Render(ID3DXSprite * pSprite)
{
	if (!m_bIsValid)
	{
		RenderDead();
		return;
	}

	D3DXMATRIX transMatrix;
	D3DXMATRIX rotMatrix;

	
	//Render player
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &m_position);
	if (m_state == PLAYER_STATE_RIGHT)
	{	
		// create the rotation matrix for the object
		D3DXMatrixRotationY(&rotMatrix, D3DXToRadian(180));
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &D3DXVECTOR2(m_position.x + m_width, m_position.y));
		D3DXMatrixMultiply(&transMatrix,&rotMatrix,&transMatrix);		
		
	}
	pSprite->SetTransform(&transMatrix);
	//if in low speed mode, show the center point
	D3DCOLOR color = m_bLowSpeedMode ? D3DCOLOR_ARGB(127, 255,255,255): D3DCOLOR_ARGB(255,255,255,255) ;
	//pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//The first 180 frames, invincible
	if (m_elapsedFrame < 180) 
	{
		m_isInvincible = true;
		
		if (m_elapsedFrame % 10 == 0)
		{
			pSprite->End();
			pSprite->Begin(D3DXSPRITE_ALPHABLEND);
			dxMgr.getD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
			//dxMgr.getD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		}
	}else
	{
		if (m_bombFrame == 0)
			m_isInvincible = false; 
		else
			m_isInvincible = true;
	}
	m_pSprite->Render(pSprite, rm.GetTexture(m_textureType), color);

	pSprite->End();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//Render ball if necessary
	if (GetPowerLevel() > 0)
	{
		//Render Left Ball
		float rotation = D3DXToRadian(6 * m_elapsedFrame);
	
		D3DXVECTOR2 centerVector(16 / 2.0f , 16 / 2.0f);//ball width 16 height 16
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL, &centerVector, -rotation, &m_ballPosition);
		pSprite->SetTransform(&transMatrix);
		//pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		m_pBallSprite->Render(pSprite, rm.GetTexture(m_textureType));//, m_elapsedFrame);
	//	pSprite->End();
		//Render Right Ball
		D3DXVECTOR2 rightPosition = m_ballPosition;
		rightPosition.x = (m_position.x + m_width / 2 - m_ballPosition.x ) * 2 + m_ballPosition.x - 16;
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL, &centerVector, rotation, &rightPosition);
		pSprite->SetTransform(&transMatrix);

	//	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		m_pBallSprite->Render(pSprite, rm.GetTexture(m_textureType));//, m_elapsedFrame);
	//	pSprite->End();
	}

}

void Player::PowerUp(int num)
{
	int lastPowerLevel = GetPowerLevel();
	m_power += num;
	if (m_power > MAX_POWER)
		m_power = MAX_POWER;
	if (m_power < 0)
		m_power = 0;
	if (GetPowerLevel() > lastPowerLevel)
	{
		//show power up and play sound
		GameObject * pObject = new GameObject(TEXTURE_ASCII, 
			new MotionInfo(0, 
			new LineTrack(D3DXVECTOR2(0, -1), 1, 0, 0, D3DXVECTOR2(m_position.x - 58 < ACTIVE_RECT_LEFT ? ACTIVE_RECT_LEFT : m_position.x - 58, m_position.y))));
		RECT srcRect;
		SetRect(&srcRect, 80, 0, 128, 8);
		pObject->SetSprite(srcRect, 1, 0, 48, 8);
		pObject->SetMaxLifeTime(60);
		pObject->SetColor(D3DCOLOR_ARGB(255, 173, 216, 230));
		gm.AddObject(pObject);
		
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_POWERUP));

	}
}

void Player::AddBomb(int delta)
{
	m_bombNum += delta;
	if (m_bombNum < 0)
		m_bombNum = 0;
}

void Player::AddLifeNum(int delta)
{
	m_lifeNum += delta;
	if (m_lifeNum < 0)
		m_lifeNum = 0;
	//play life extend wav
	if (delta > 0)
	{
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_EXTEND));
	}
}		

int Player::GetPowerLevel()
{
	if (m_power < 8)
		return 0;
	else
		if (m_power < 16)
			return 1;
		else
			if (m_power < 32)
				return 2;
			else
				if (m_power < 128)
					return 3;
				return 4;
}

//--------------------------------------------------------------------------------------
//Called when the player is missed
//--------------------------------------------------------------------------------------
void	Player::OnWipped()
{
	if (m_lifeNum > 0)
	{
		//show dead circle
		EffectWhiteCircle* eff = new EffectWhiteCircle(GetCenter());
		eff->SetMaxLifeTime(PLAYER_DEAD_TIME / 2);
		gm.AddObject(eff);
		//reduce current power and add power items
		float tempSpeed[] = {2.5f, 3.0f, 5.0f, 4.0f, 3.5f, 3.0f};
		D3DXVECTOR2 tempDirection[] = {D3DXVECTOR2(-1,-1), D3DXVECTOR2(-1,-1.5), D3DXVECTOR2(1, -2), D3DXVECTOR2(1,-1), D3DXVECTOR2(1,-1), D3DXVECTOR2(1,-1)};
		for (int i = 0 ; i < 6; i ++)
		{
			ITEM_TYPE itemType;
			if (i != 5)
				itemType = ITEM_TYPE_POWER;
				
			else
				itemType = ITEM_TYPE_BIGPOWER;

			Item *pItem = &ItemFactory::GetItem(itemType, this->GetCenter());
			pItem->ClearMotionInfo();
			pItem->motionIndex = 0;
			pItem->motionInfos.push_back(new MotionInfo(0, new LineTrack(tempDirection[i], tempSpeed[i],0, 0),true));
			pItem->motionInfos.push_back(new MotionInfo(60, new StaticTrack(60), true));
			pItem->motionInfos.push_back(new MotionInfo(70, new LineTrack(D3DXVECTOR2(0, 1), 4, 0, 70), true));
			gm.AddItem(pItem);
		}
		
		PowerUp(-16);

		SetState(PLAYER_STATE_NORMAL);
		m_bIsValid = false;
		m_isInvincible = true;
		m_elapsedFrame = 0;
	//	m_lifeNum --;
	//	Init();
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_PLDEAD));
		gm.ClearBullets();
		
	}		
	else
	//GameOver
	{
		MessageBox(NULL,"Game Over!", "Game Over!", MB_OK);
		PostMessage(NULL,WM_QUIT,NULL,NULL);
	}

}
//--------------------------------------------------------------------------------------
//Render Dead Effect: first half dead time, scale player's height  to 4 times 
//in the dead place,then move to the default start position and scale height from 4 to 1 
//time(s) 						
//--------------------------------------------------------------------------------------
void	Player::RenderDead()
{
	
	D3DXMATRIX transMatrix;
	D3DXVECTOR2 translationVector;
	float scale;
	if (m_elapsedFrame < PLAYER_DEAD_TIME / 2)
	{
		scale = 1 + m_elapsedFrame * 4.0f / PLAYER_DEAD_TIME;
		translationVector.x = m_position.x;
		translationVector.y = m_position.y;
	}
	else
	{
		scale = 3 - (m_elapsedFrame - PLAYER_DEAD_TIME / 2) * 4.0f / PLAYER_DEAD_TIME;
		translationVector.x = PLAYER_START_POS_X;
		translationVector.y =  PLAYER_START_POS_Y;
	}
	//dxMgr.GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&transMatrix, &D3DXVECTOR2(m_width / 2.0f, m_height / 2.0f), 0.0f,
		&D3DXVECTOR2(1.0f, scale),NULL, 0.0f, &translationVector);
	dxMgr.GetSprite()->SetTransform(&transMatrix);
	m_pSprite->Render(dxMgr.GetSprite(), rm.GetTexture(TEXTURE_PLAYER_00), D3DCOLOR_ARGB(127, 255,255,255));
	//dxMgr.GetSprite()->End();
}

void Player::OnGrazed()
{
	m_grazeNum++;
	dsMgr.playSound(rm.GetSoundBuffer(SOUND_GRAZE));
	gm.AddScore(100);
}