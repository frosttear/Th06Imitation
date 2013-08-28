//--------------------------------------------------------------------------------------
//File: GameManager.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include <windows.h>
#include ".\GameManager.h"
#include "Player.h"
#include "GameObject.h"
#include "GameSprite.h"
#include "Bullet.h"
#include "Item.h"
#include "Collision.h"
#include "EnemyCreator.h"
#include "Stage1Enemy.h"
#include "Effect.h"
#include <vector>
//--------------------------------------------------------------------------------------
// Init 
//--------------------------------------------------------------------------------------
GameManager::GameManager()
{
	m_pPlayer						= NULL;
	m_state							= GAME_STATE_INIT;
	m_selectedIndex					= 0;
	m_score							= 6120;
	m_highestScore					= 69602630;
	QueryPerformanceFrequency(&timerFreq);
	m_anim_rate						= 60;
	m_difficulty					= 1;
	D3DXFONT_DESC fontDesc;
	ZeroMemory(&fontDesc, sizeof(D3DXFONT_DESC));
	m_pTextRender					= new TextRender(fontDesc, "");
}

GameManager::~GameManager()
{
	DeleteAllObjects();
	/*for (int i =0 ; i < TEXTURE_NUM; i ++)
	{
		if (m_pTextures[i] != NULL)
			m_pTextures[i]->Release();
	}*/

}

//Load textures to memory
//void	GameManager::LoadTexture()
//{
//
//	for (int i = 0 ; i < TEXTURE_NUM; i ++)
//	{
//		if (FAILED(D3DXCreateTextureFromFile(dxMgr.getD3DDevice(),(TEXTURE_PATH + TEXTURE_FILENAME[i]).c_str(),&m_pTextures[i])))
//		{
//			MessageBox(NULL, ("unable to load texture from file" + TEXTURE_FILENAME[i]).c_str(), "ERROR", MB_OK);
//		}
//	}
//	m_background = rm.GetTexture(TEXTURE_STG2BG);
//}

//void	GameManager::LoadSound()
//{
//	for (int i = 0; i < SOUND_NUM; i++)
//	{
//		m_soundBuffers[i]	= dsMgr.LoadWaveToSoundBuffer(SOUND_PATH + SOUND_FILENAME[i]);
//
//	}
//
//	for (int i = 0; i < BGM_NUM; i ++)
//	{
//		m_bgmBuffers[i]	= dsMgr.LoadWaveToSoundBuffer(BGM_PATH + BGM_FILENAME[i]);
//	}
//}

void	GameManager::RenderBackground()
{
	D3DXMATRIX transMatrix;
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,&D3DXVECTOR2(2, 2),NULL, 0.0f, &D3DXVECTOR2(ACTIVE_RECT_LEFT, ACTIVE_RECT_TOP));
	ID3DXSprite * pSprite = dxMgr.GetSprite();
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(m_background, NULL, NULL, NULL, D3DCOLOR_RGBA(255,255,255,196));
}


//--------------------------------------------------------------------------------------
//Render
//Called once per frame to render background ,all objects in the  m_objects list and 
//Player 
//--------------------------------------------------------------------------------------
void	GameManager::Render()
{	
	dxMgr.beginRender();
	switch (m_state)
	{
	case GAME_STATE_RUN:
		RenderBattleScene();
		break;
	case GAME_STATE_PAUSE:
		RenderBattleScene();
		RenderPauseMenu();
		break;
	case GAME_STATE_TITLE:
		RenderTitle();
		break;
	case GAME_STATE_STAGE_CLEAR:
		RenderStageClear();
		break;
	case GAME_STATE_CHAT:
		RenderBattleScene();
		RenderChatDialog();
		break;
	default:
		break;
	}
	dxMgr.endRender();
	LARGE_INTEGER last = timeStart;
	QueryPerformanceCounter(&timeStart);

	if (m_stateElapsedFrame % 30 == 0)
		m_anim_rate = timerFreq.QuadPart / ( (float)timeStart.QuadPart - (float)last.QuadPart );


}

void	GameManager::RenderBattleScene()
{
	//render background

	ID3DXSprite * pSprite = dxMgr.GetSprite();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	RenderBackground();
	//Render Objects
	for (std::list<GameObject *>::iterator iterObj = m_objects.begin(); iterObj != m_objects.end(); iterObj ++)
	{
		(*iterObj)->Render(dxMgr.GetSprite());
	}
	//Render Player
	//if (m_state != GAME_STATE_STAGE_CLEAR)
		m_pPlayer->Render(dxMgr.GetSprite());

	RenderFront();
	pSprite->End();
}
void	GameManager::RenderPauseMenu()
{
	ID3DXSprite * pSprite = dxMgr.GetSprite();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//render “游戏暂停”
	RECT srcRect;
	SetRect(&srcRect, 0, 158, 64, 174);  
	D3DXMATRIX transMatrix;
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,&D3DXVECTOR2(1.2f, 1.2f),NULL, 0.0f, &D3DXVECTOR2(ACTIVE_RECT_CENTER_X - 32, ACTIVE_RECT_CENTER_Y - 100));
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_ASCII), &srcRect, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//render menu item
	SetRect(&srcRect, 0, 174, 64, 190);
	if (m_selectedIndex == 0)
	{
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,&D3DXVECTOR2(1.5f, 1.5f),NULL, 0.0f, &D3DXVECTOR2(ACTIVE_RECT_CENTER_X - 48, ACTIVE_RECT_CENTER_Y - 30));
		pSprite->SetTransform(&transMatrix);
		pSprite->Draw(rm.GetTexture(TEXTURE_ASCII_S), &srcRect, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		SetRect(&srcRect, 0, 190, 96, 206);
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,&D3DXVECTOR2(1.2f, 1.2f),NULL, 0.0f, &D3DXVECTOR2(ACTIVE_RECT_CENTER_X - 48, ACTIVE_RECT_CENTER_Y + 10));
		pSprite->SetTransform(&transMatrix);
		pSprite->Draw(rm.GetTexture(TEXTURE_ASCII), &srcRect, NULL, NULL, D3DCOLOR_ARGB(255, 100, 100, 100));

	}
	else
	{
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,&D3DXVECTOR2(1.2f, 1.2f),NULL, 0.0f, &D3DXVECTOR2(ACTIVE_RECT_CENTER_X - 48, ACTIVE_RECT_CENTER_Y - 30));
		pSprite->SetTransform(&transMatrix);
		pSprite->Draw(rm.GetTexture(TEXTURE_ASCII), &srcRect, NULL, NULL, D3DCOLOR_ARGB(255, 100, 100,100));

		SetRect(&srcRect, 0, 190, 96, 206);
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,&D3DXVECTOR2(1.5f, 1.5f),NULL, 0.0f, &D3DXVECTOR2(ACTIVE_RECT_CENTER_X - 48, ACTIVE_RECT_CENTER_Y + 10));
		pSprite->SetTransform(&transMatrix);
		pSprite->Draw(rm.GetTexture(TEXTURE_ASCII_S), &srcRect, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	


	pSprite->SetTransform(&transMatrix);
	pSprite->End();
}
//--------------------------------------------------------------------------------------
//	RenderTitle
//	
//--------------------------------------------------------------------------------------
void	GameManager::RenderTitle()
{
	int itemNum	= 8;
	ID3DXSprite * pSprite = dxMgr.GetSprite();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//render background img
	D3DXMATRIX transMatrix;
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,&D3DXVECTOR2(0.625f, 1.0f),NULL, 0.0f, &D3DXVECTOR2(0, 0));
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_TITLE), NULL, NULL, NULL, D3DCOLOR_ARGB(195, 255, 255, 255));
	//render Title Menu Items
	D3DXVECTOR2 startPos(450, 220);
	for (int i = 0; i < itemNum;  i ++)
	{
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,&D3DXVECTOR2(1.0f, 1.0f),NULL, 0.0f, &startPos);
		TextureType textureType = TEXTURE_TITLE_01;
		int	alpha = 127;
		if (m_selectedIndex == i)
		{
			D3DXVECTOR2 temp = startPos + D3DXVECTOR2(-5, -5);
			D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,&D3DXVECTOR2(1.0f, 1.0f),NULL, 0.0f, &temp);			
			textureType = TEXTURE_TITLE_01S;
			alpha		= 255;
		}
		
		pSprite->SetTransform(&transMatrix);
		pSprite->Draw(rm.GetTexture(textureType), &TITLE_MENU_ITEM_RECT[i], NULL, NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));
		startPos += D3DXVECTOR2(-10, 30);
	}
	pSprite->End();
}
void	GameManager::RenderFront()
{
	const int START_X = 432;
	const int START_Y = 64;
	const int MAX_LIFE_SHOW = 9;
	const int MAX_BOMB_SHOW = 9;
	ID3DXSprite * pSprite = dxMgr.GetSprite();
	
	RECT srcRect;
	//render background
	D3DXVECTOR2 position(0, 0);
	D3DXMATRIX transMatrix;
	for (int i = 0; i < SCR_WIDTH / 32 ; i ++)
	{
		for (int j = 0 ; j < SCR_HEIGHT / 32; j ++)
		{
			position.x = i * 32.0f;
			position.y = j * 32.0f;
			if (position.x >= ACTIVE_RECT_LEFT && position.x + 32 <= ACTIVE_RECT_RIGHT && position.y >=ACTIVE_RECT_TOP && position.y + 32<= ACTIVE_RECT_BOTTOM)
			{
				continue;
			}
			D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
			pSprite->SetTransform(&transMatrix);
			SetRect(&srcRect, 0, 224, 32, 256);
			pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));
		}
	}
	//render highest score text
	SetRect(&srcRect, 0, 192, 64, 208);
	position.x = START_X;
	position.y = START_Y;
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));

	position.x += 64;
	RenderNumber(m_highestScore, 9, &position);

	//render current score text
	SetRect(&srcRect, 0, 208, 32, 224);
	position.x = START_X;
	position.y += 24;
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));
	//render score num
	position.x += 64;
	RenderNumber(m_score, 9, &position);
	
	//render life
	SetRect(&srcRect, 0, 176, 64, 192);
	position.x = START_X;
	position.y += 48;
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));

	//render life stars
	SetRect(&srcRect, 32, 240, 48, 256);
	position.x += 64;
	for (int i = 0; i < MAX_LIFE_SHOW && i < m_pPlayer->GetLifeNum(); i++)
	{
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
		pSprite->SetTransform(&transMatrix);
		pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));
		position.x += 16;
	}
	//render bomb
	SetRect(&srcRect, 0, 160, 48, 176);
	position.x = START_X;
	position.y += 24;
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));

	//render bomb stars
	SetRect(&srcRect, 48, 240, 64, 256);
	position.x += 64;
	for (int i = 0; i < MAX_BOMB_SHOW && i < m_pPlayer->GetBombNum(); i++)
	{
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
		pSprite->SetTransform(&transMatrix);
		pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));
		position.x += 16;
	}

	//render power
	SetRect(&srcRect, 32, 208, 80, 224);
	position.x = START_X;
	position.y += 48;
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));

	//render power number
	position.x += 64;
	if (m_pPlayer->GetPower() < 128)
		RenderNumber(m_pPlayer->GetPower(), 0, &position);
	else
	{
		SetRect(&srcRect, 64, 240, 112, 256);
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
		pSprite->SetTransform(&transMatrix);
		pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));

	}
	//render graze
	SetRect(&srcRect, 32, 224, 80, 240);
	position.x = START_X;
	position.y += 24;
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));	
	//render graze num
	position.x += 64;
	RenderNumber(m_pPlayer->GetGrazeNum(), 0, &position);
	//render point
	SetRect(&srcRect, 48, 160, 64, 176);
	position.x = START_X;
	position.y += 24;
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));	//render point

	//render point num 
	position.x += 64;
	RenderNumber(m_pPlayer->GetPointNum(), 0, &position);
	
	//render logo
	//render rect
	position.x = START_X + 32;
	position.y += 80;
	SetRect(&srcRect, 128, 128, 256, 256);
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));
	//render dong
	position.x = START_X + 8;
	position.y -= 24;
	SetRect(&srcRect, 0, 0, 64, 64);
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,127));	
	
	//render fang
	position.x += 56;
	SetRect(&srcRect, 64, 0, 128, 64);
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,127));	
	//render hong
	//position.x = START_X + 48;
	position.y += 56;
	SetRect(&srcRect, 128, 0, 192, 64);
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,255));
	
	//render mo
	//position.x = START_X + 64;
	position.y += 56;
	SetRect(&srcRect, 192, 0, 256, 64);
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,127));
	//render xiang
	position.x += 56;
	SetRect(&srcRect, 0, 64, 64, 128);
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &position);
	pSprite->SetTransform(&transMatrix);
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255,255,255,127));
	
	//render fps
	position.y += 56;
	char temp[10];
	sprintf(temp, "%.2f", m_anim_rate);
	RenderAsciiText(temp, &position);
	//RenderNumber((int)m_anim_rate, 2, &position);
	//position.x += 8;
	//RenderNumber((int)((m_anim_rate - (int)m_anim_rate) * 100), 2, &position);
	//RenderNumber(currentTime, 4, &position);
}
void	GameManager::RenderNumber(const int number,const int count, D3DXVECTOR2 * pPosition, D3DCOLOR color, TextureType textureType)
{
	int temp = number;
	std::vector<int> nums;
	ID3DXSprite * pSprite = dxMgr.GetSprite();
	int i = 0;
	do
	{
		nums.push_back(temp % 10);
		temp /= 10;
	}
	while ((count > 0 && ++i < count)|| (temp != 0 && count == 0));
	for (i = (int)nums.size() - 1; i >=0; i --)
	{
		RECT srcRect = rm.GetRectOfDigit(nums[i]);
		D3DXMATRIX transMatrix;
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, pPosition);
		pSprite->SetTransform(&transMatrix);
		pSprite->Draw(rm.GetTexture(textureType), &srcRect, NULL, NULL, color);
		pPosition->x += 15.0;
	}
}


//-------------------------------------------------------------------------------------
//Change ASCII Text to Char Pictures
//
//-------------------------------------------------------------------------------------
void	GameManager::RenderAsciiText(std::string text,  D3DXVECTOR2 * pPosition, D3DCOLOR color, TextureType textureType)
{
	ID3DXSprite * pSprite = dxMgr.GetSprite();
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		if (text[i] >= 0  && text[i] <= 128)
		{
			RECT srcRect = rm.GetRectOfAscii(text[i]);
			D3DXMATRIX transMatrix;
			D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, pPosition);
			pSprite->SetTransform(&transMatrix);
			pSprite->Draw(rm.GetTexture(textureType), &srcRect, NULL, NULL, color);
			pPosition->x += 16.0;
		}
	}
}
void	GameManager::RenderStageClear()
{
	ID3DXSprite * pSprite = dxMgr.GetSprite();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	RenderBackground();
	int tempScore	= 0;
	float tempFactor  = 1.0;
	float totalFactor = 1.0;
	int totalScore	= 0;
	const int START_X = 64;
	D3DXVECTOR2 startPosition(100, 150);
	RenderAsciiText("Stage Clear", &startPosition, D3DCOLOR_ARGB(255, 255, 255, 0));
	startPosition.x = START_X;
	startPosition.y += 32;
	RenderAsciiText("Stage * 1000 = ", &startPosition, D3DCOLOR_ARGB(255, 255, 255,255));
	tempScore = m_stage * 1000;
	RenderNumber(tempScore, 0, &startPosition , D3DCOLOR_ARGB(255, 255, 255, 255));
	startPosition.x = START_X;
	startPosition.y += 16;
	RenderAsciiText("Power *  100 = ", &startPosition, D3DCOLOR_ARGB(255, 255, 255, 255));
	tempScore = m_pPlayer->GetPower() * 100;
	RenderNumber(tempScore, 0, &startPosition , D3DCOLOR_ARGB(255, 255, 255, 255));
	totalScore += tempScore;
	startPosition.x = START_X;
	startPosition.y += 16;
	RenderAsciiText("Graze *   10 = ", &startPosition, D3DCOLOR_ARGB(255, 255, 255, 255));
	tempScore = m_pPlayer->GetGrazeNum() * 10;
	RenderNumber(tempScore, 0, &startPosition , D3DCOLOR_ARGB(255, 255, 255, 255));
	totalScore += tempScore;
	startPosition.x = START_X + 64;
	startPosition.y += 16;
	RenderAsciiText("* Point Item  ", &startPosition, D3DCOLOR_ARGB(255, 255, 255, 255), TEXTURE_ASCII_S);
	tempFactor = (float)m_pPlayer->GetPointNum();
	RenderNumber((int)tempFactor, 0, &startPosition , D3DCOLOR_ARGB(255, 255, 255, 255), TEXTURE_ASCII_S);
	totalFactor *= tempFactor;
	startPosition.x = START_X;
	startPosition.y += 32;
	
	//TODO: Difficulty Factor should be setted according to current Difficulty 
	RenderAsciiText("Normal Rank    *  ", &startPosition, D3DCOLOR_ARGB(255, 255, 255, 255), TEXTURE_ASCII_S);
	tempFactor	= 1.0;
	char temp[64];
	sprintf(temp, "%.1f", tempFactor);
	//tempString = ;
	RenderAsciiText(temp, &startPosition, D3DCOLOR_ARGB(255, 255, 255, 255), TEXTURE_ASCII_S);
	//RenderNumber((int)tempFactor, 0, &startPosition, D3DCOLOR_ARGB(255, 255, 255, 255), TEXTURE_ASCII_S);
	//tempFactor - (int)tempFactor
//	RenderNumber(
	//RenderNumber(tempScore, 0, &startPosition , D3DCOLOR_ARGB(255, 255, 0, 0));
	totalFactor *= tempFactor;
	startPosition.y += 16;
	startPosition.x = START_X;
	RenderAsciiText("Total     =    ", &startPosition, D3DCOLOR_ARGB(255, 255, 255, 255));
	RenderNumber((int)(totalScore * totalFactor), 0, &startPosition , D3DCOLOR_ARGB(255, 255, 255, 255));
	RenderFront();
	pSprite->End();
}

void	GameManager::RenderChatDialog()
{
	ID3DXSprite *pSprite = dxMgr.GetSprite();
	dxMgr.beginRender();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	RECT rect;
	SetRect(&rect, 128, 128, 256, 256);
	//pSprite->Draw(rm.GetTexture(TEXTURE_ASCII), &rect, NULL, )
	pSprite->End();
}
//--------------------------------------------------------------------------------------
//  Update
//	This function is called once per frame. It's used to get the user
//	input ,update object's position, do intersecting and delete invalid objects.
//--------------------------------------------------------------------------------------
void	GameManager::Update()
{
	//diMgr.getInput();
	
	switch(m_state)
	{

		case GAME_STATE_RUN:
			GameStateRun();
			break;
		case GAME_STATE_PAUSE:
			GameStatePause();
			break;
		case GAME_STATE_INIT:
			GameStateInit();
			break;
		case GAME_STATE_TITLE:
			GameStateTitle();
			break;
		case GAME_STATE_STAGE_CLEAR:
			GameStateStageClear();
			break;
		case GAME_STATE_END:
			GameStateEnd();
			break;
		case GAME_STATE_CHAT:
			GameStateChat();
			break;
	}
}

DWORD	GameManager::GameStateTitle()
{
	int menuItemNum = 8;
	diMgr.GetBufferedInput();

	if (diMgr.isKeyPressed(DIK_Z) || diMgr.isKeyPressed(DIK_RETURN))
	{
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_OK));
		switch (m_selectedIndex)
		{
		case 0:
			//Start
			m_stateElapsedFrame = 0;
			if (m_pPlayer != NULL)
				delete m_pPlayer;
			m_pPlayer	= new Player();
			m_stage = 1;
			InitStage(m_stage);
			m_state = GAME_STATE_RUN;
			return GAME_STATE_RUN;
			break;
		case 1:
			//Extra Start
			break;
		case 2:
			//Practice Start
			break;
		case 3:
			//Replay
			break;
		case 4:
			//Score
			break;
		case 5:
			//MusicRoom
			break;
		case 6:
			//Option
			break;
		case 7:
			//Quit
			PostQuitMessage(0);
			break;
		default:
			break;
		}
	}//end of if (diMgr.isKeyPressed(DIK_Z))

	if (diMgr.isKeyPressed(DIK_UP))
	{
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_SELECT));
		m_selectedIndex --;
		if (m_selectedIndex < 0)
			m_selectedIndex = menuItemNum - 1;
	}
	if (diMgr.isKeyPressed(DIK_DOWN))
	{
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_SELECT));
		m_selectedIndex ++;
		if (m_selectedIndex > menuItemNum - 1)
			m_selectedIndex = 0;
	}
	return GAME_STATE_TITLE;
}

DWORD	GameManager::GameStatePause()
{
	int menuItemNum = 2;
	diMgr.GetBufferedInput();

	if (diMgr.isKeyPressed(DIK_Z))
	{
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_OK));
		if (m_selectedIndex == 0)
		{
			Sleep(500);
			m_state = GAME_STATE_RUN;
			return GAME_STATE_RUN;
		}
		else
		{
			m_selectedIndex = 0;
			DeleteAllObjects();
			ChangeBGM(rm.GetBGMBuffer(BGM_TITLE));
			delete m_pPlayer;
			m_pPlayer = NULL;
			m_state = GAME_STATE_TITLE;
			return GAME_STATE_TITLE;
		}
	}
	if (diMgr.isKeyPressed(DIK_ESCAPE)|| diMgr.isKeyPressed(DIK_X))
	{
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_CANCEL));
		Sleep(500);
		m_state = GAME_STATE_RUN;
		return GAME_STATE_RUN;
	}
	if (diMgr.isKeyPressed(DIK_UP))
	{
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_SELECT));
		m_selectedIndex --;
		if (m_selectedIndex < 0)
			m_selectedIndex = menuItemNum - 1;
		return GAME_STATE_PAUSE;
	}
	if (diMgr.isKeyPressed(DIK_DOWN))
	{
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_SELECT));
		m_selectedIndex ++;
		if (m_selectedIndex > menuItemNum - 1)
			m_selectedIndex = 0;
		return GAME_STATE_PAUSE;
	}
	return GAME_STATE_PAUSE;
	
}

DWORD	GameManager::GameStateRun()
{
	diMgr.getInput();
	//diMgr.GetBufferedInput();
	if (diMgr.isKeyPressed(DIK_ESCAPE))
	{
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_CANCEL));
		m_selectedIndex = 0;
		Sleep(500);
		m_state = GAME_STATE_PAUSE;
		return GAME_STATE_PAUSE;
	}
	else
	{
		ec.CreateEnemy();
		ec.CreateBossOfStage(1);
		m_stateElapsedFrame ++;
	
		//delete last frame's invalid obj
		std::list<GameObject *>::iterator iterObj;
		
		for (iterObj = m_objects.begin(); iterObj != m_objects.end();)
		{
			GameObject * pObject = *iterObj;
			if (!(pObject)->IsValid())
			{
				iterObj = m_objects.erase(iterObj);
				pObject->OnWipped();
				if (pObject != NULL)
					delete pObject;
				pObject = NULL;
			}else
			{
				iterObj++;
			}
		}
		//update all objects
		m_pPlayer->Update();		
		for (iterObj = m_objects.begin(); iterObj != m_objects.end(); iterObj ++)
		{
			if (((GameObject*)*iterObj)->IsValid())
				((GameObject *)*iterObj)->Update();
		}
		//check collision
		Collision();
		
		if (m_score > m_highestScore )
			m_highestScore = m_score;
		return GAME_STATE_RUN;
	}//end of if (diMgr.isKeyDown(DIK_ESCAPE))
	
}
//--------------------------------------------------------------------------------------
//DESC: Init 
//--------------------------------------------------------------------------------------
DWORD	GameManager::GameStateInit()
{
	m_stateElapsedFrame		= 0;
	if (m_pPlayer != NULL)
		delete m_pPlayer;
	m_pPlayer		= new Player();

	//show logo while loading
	IDirect3DSurface9*	bkgrd = dxMgr.getSurfaceFromBitmap("./img/th06logo.jpg");;
	dxMgr.beginRender();
	dxMgr.blitToSurface(bkgrd, NULL, NULL);
	dxMgr.endRender();
	rm.LoadResource();
	//m_pResourceManager->LoadSound();
	ChangeBGM(rm.GetBGMBuffer(BGM_TITLE));
	if (bkgrd != NULL) 
		bkgrd->Release();
	//ec.CreateEnemyOfStage(1);
	//ec.LoadEnemy("stg1.std");
	m_state = GAME_STATE_TITLE;
	//OnStageClear();
	return GAME_STATE_TITLE;
}
DWORD	GameManager::GameStateStageClear()
{


	m_stateElapsedFrame++;
	if (m_stateElapsedFrame > 60 * 10)
	{
		m_stage ++;
		DeleteAllObjects();
		InitStage(m_stage);
		m_state = GAME_STATE_RUN;
		return GAME_STATE_RUN;
	}
	/*m_stage++;
	currentTime = 0;*/
	return GAME_STATE_STAGE_CLEAR;
}
DWORD	GameManager::GameStateEnd()
{
	m_stateElapsedFrame++;
	if (m_stateElapsedFrame < 60 * 10)
	{
		GameStateStageClear();
	}
	else
	{
	}
	m_state = GAME_STATE_END;
	return GAME_STATE_END;
}
void	GameManager::OnStageClear()
{
	m_stateElapsedFrame = 0;
	if (m_stage >= MAX_STAGE_NUM)
	{
		
		m_state = GAME_STATE_END;
	}else
	{
		m_state = GAME_STATE_STAGE_CLEAR;
		/*D3DXFONT_DESC d3dFont;
		ZeroMemory(&d3dFont, sizeof(d3dFont));
		strcpy(d3dFont.FaceName,  "Times New Roman");
		d3dFont.Italic	= TRUE;
		d3dFont.CharSet = DEFAULT_CHARSET;
		d3dFont.Width	= 8;
		d3dFont.Height	= 16;
		d3dFont.Weight	= 500;
		RECT rect = {50,100,150,150};
		m_pTextRender->SetFontDesc(d3dFont);
		EffectText *pEffectText = new EffectText(m_pTextRender, rect, D3DCOLOR_ARGB(255,0,255,255));
		pEffectText->SetText("Stage Clear");
		pEffectText->SetMaxLifeTime(60 * 10);
		AddObject(pEffectText);*/
		m_background =  rm.GetTexture(TEXTURE_LOADING);

	}
}
DWORD	GameManager::GameStateChat()
{
	const int  CHAT_INTERVAL = 240;
	//Get chat text and character
	std::string text = "Test";
	++m_stateElapsedFrame;
	if (m_stateElapsedFrame % CHAT_INTERVAL == 0)
	{
		//auto change until
	}
	return 0;
}
//--------------------------------------------------------------------------------------
//Make collision check 
//--------------------------------------------------------------------------------------
void	GameManager::Collision()
{
	//check player and items 
	RECT playerRect = m_pPlayer->GetRect();
	
	for ( std::list<Item *>::iterator i = m_items.begin(); i != m_items.end();)
	{
		Item * pItem = *i++;
		if (m_pPlayer->IsValid())
		{
			if (m_pPlayer->GetCenter().y < MAX_POINT_LINE)
			{
				if (pItem->GetMotionInfo()->pTarget != m_pPlayer)
				{
					pItem->ClearMotionInfo();
					pItem->motionInfos.push_back(new MotionInfo(pItem->GetElapsedFrame(), 
						new LineTrack(m_pPlayer->GetCenter() - pItem->GetCenter(), 30.0f, 0.0f, (float)pItem->GetElapsedFrame(), pItem->GetPosition()), true, m_pPlayer, D3DXVECTOR2(0,0), true));
					pItem->motionIndex = 0;
				}
			}
			if (Collision::CollisionRect(&playerRect, &pItem->GetRect()))
			{
				m_pPlayer->AddLifeNum(pItem->GetLife());
				m_pPlayer->PowerUp(pItem->GetPower());
				m_pPlayer->AddBomb(pItem->GetBomb());
				m_score += pItem->GetScore();
				if (pItem->GetItemType() == ITEM_TYPE_POINT)
					m_pPlayer->AddPointNum(1);
				pItem->SetValid(false);
			}
		}
	}

	//check player and bullets
	for ( std::list<Bullet *>::iterator i = m_bullets.begin(); i != m_bullets.end();)
	{
	
		Bullet * pBullet = *i++;
		if (pBullet->IsValid() && !pBullet->IsPlayer() && m_pPlayer->IsValid())
		{
			//Check graze
			//int grazeInterval = 3;
			//if (currentTime % grazeInterval == 0)
			if (!pBullet->IsGrazed())
			{
				//set player's collision radius to graze radius, then check collsion
				m_pPlayer->SetCollisionInfo(new CollisionCircle(m_pPlayer->GetGrazeRadius()));
				if (pBullet->Collision(m_pPlayer))
				{
					m_pPlayer->OnGrazed();
					pBullet->SetIsGrazed(true);
				}
				//restore collision radius
				m_pPlayer->SetCollisionInfo(new CollisionCircle(m_pPlayer->GetCollisionRadius()));
			}
			//Check collision
			if (pBullet->Collision(m_pPlayer))
			{
				pBullet->SetValid(false);
				if (!m_pPlayer->IsInvincible())
				{
					m_pPlayer->OnWipped();
					break;
				}
			}
		}
	}//end of bullet's check

	//check enmy and self bullets
	for ( std::list<Enemy *>::iterator  i = m_enemies.begin(); i != m_enemies.end();)
	{
		Enemy * pEnemy = *i ++;
		RECT enemyRect = pEnemy->GetRect();
		
		if (pEnemy->IsValid() && m_pPlayer->IsValid() 
			&& Collision::CollisionCircleRect(&enemyRect,((CollisionCircle*)m_pPlayer->GetCollisionInfo())->radius, &m_pPlayer->GetCenter()))
		{
			pEnemy->OnHit(m_pPlayer);
			if (!m_pPlayer->IsInvincible())
			{
				m_pPlayer->OnWipped();
			}
		}
		if (!pEnemy->IsValid())
			continue;
		for ( std::list<Bullet *>::iterator j = m_bullets.begin(); j != m_bullets.end();)
		{
			if (!pEnemy->IsValid())
				break;
			Bullet * pBullet = *j ++;
			if (!pBullet->IsValid())
				continue;
			if ((pBullet)->IsPlayer())
			{
				if (pBullet->Collision(pEnemy))
				{
					pEnemy->OnHit(pBullet);					
					pBullet->SetValid(false);
				}
			}
		}
	}

}

void	GameManager::RemoveBullet(Bullet *pBullet)
{
	for (std::list<Bullet *>::iterator i = m_bullets.begin(); i != m_bullets.end(); )
	{
		
		if ((*i) != pBullet)
		{
			i++;
		}else
		{
			i = m_bullets.erase(i);
		}
		

	}
}

void	GameManager::RemoveItem(Item * pItem)
{
	for (std::list<Item *>::iterator i = m_items.begin(); i != m_items.end(); )
	{
		if (*i != pItem)
		{
			i++;
		}else
		{
			i = m_items.erase(i);
		}
		

	}
}

void	GameManager::RemoveEnemy(Enemy * pEnemy)
{
	for (std::list<Enemy *>::iterator i = m_enemies.begin(); i != m_enemies.end(); )
	{
		if (*i != pEnemy)
		{
			i++;
		}else
		{
			i = m_enemies.erase(i);
		}
		

	}
}

//-----------------------------------------------------------------------------
//返回敌机列表中第一个有效敌机(作为自机跟踪弹跟踪目标等)
//-----------------------------------------------------------------------------
Enemy*	GameManager::GetEnemy()
{
	for (std::list<Enemy *>::iterator i = m_enemies.begin(); i != m_enemies.end(); ++i)
	{
		if ((*i)->IsValid())
			return *i;
	}
	return NULL;
}
//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//Clear all enmy's bullets
//--------------------------------------------------------------------------------------
void	GameManager::ClearBullets(void)
{
	for (std::list<Bullet *>::iterator i = m_bullets.begin(); i != m_bullets.end(); ++i)
	{
		if (!(*i)->IsPlayer())
			(*i)->SetValid(false);
	}
}
//--------------------------------------------------------------------------------------
//Called when boss change phases or player bombs,clear all enmy's bullets and change 
//them to stars
//--------------------------------------------------------------------------------------
//Change enemy Bullets to Stars
void	GameManager::ChangeBulletsToStars(void)
{
	for (std::list<Bullet *>::iterator i = m_bullets.begin(); i != m_bullets.end(); ++i)
	{
		if (!(*i)->IsPlayer())
		{
			(*i)->SetValid(false);
			Item *pItem = &ItemFactory::GetItem(ITEM_TYPE_STAR, (*i)->GetCenter());
			//pItem->SetMaxLifeTime(180);
			//pItem->ClearMotionInfo();
			//pItem->motionInfos.push_back(new MotionInfo(0, new StaticTrack(0, (*i)->GetCenter())));
			AddItem(pItem);
			//AddScore(pItem->GetScore());
		}
	}
}

//--------------------------------------------------------------------------------------
//Remove all objects while quit  run state,PS:DON'T delete Player!!
//--------------------------------------------------------------------------------------
void	GameManager::DeleteAllObjects(void)
{
	
	for (std::list<Bullet*>::iterator i = m_bullets.begin(); i != m_bullets.end();)
	{
		i = m_bullets.erase(i);
	}

	for (std::list<Item*>::iterator i = m_items.begin(); i != m_items.end();)
	{
		i = m_items.erase(i);
	}
	for (std::list<Enemy*>::iterator i = m_enemies.begin(); i != m_enemies.end();)
	{
		i = m_enemies.erase(i);
	}
	for (std::list<GameObject *>::iterator i = m_objects.begin(); i != m_objects.end();)
	{
		GameObject * tempP = (GameObject*) *i;
		i = m_objects.erase(i);
		if (tempP != NULL)
		{
			delete tempP;
			tempP = NULL;
		}
	}
}





//-------------------------------------------------------------------
//GetBackgroundOfStage
//获取指定关卡的背景
//-------------------------------------------------------------------
LPDIRECT3DTEXTURE9	GameManager::GetBackgroundOfStage(int stage)
{
	switch (stage)
	{
	case 1:
		return rm.GetTexture(TEXTURE_STG1BG);
		break;
	case 2:
		return rm.GetTexture(TEXTURE_STG2BG);
		break;
	default:
		return rm.GetTexture(TEXTURE_STG1BG);
	}
}
//-------------------------------------------------------------------
//GetBGMOfStage
//获取指定关卡的默认BGM
//-------------------------------------------------------------------
LPDIRECTSOUNDBUFFER GameManager::GetBGMOfStage(int stage)
{
	switch (stage)
	{
	case 1:
		return rm.GetBGMBuffer(BGM_STG1);
	case 2:
		return rm.GetBGMBuffer(BGM_STG2);
	default:
		return rm.GetBGMBuffer(BGM_TITLE);
	}
}
void	GameManager::InitStage(int stage)
{

	//Create Enemy
	m_stateElapsedFrame = 0;
	ec.CreateEnemyOfStage(stage);
	//Change Background IMG
	m_background = GetBackgroundOfStage(stage);
	//Change BGM
	ChangeBGM(GetBGMOfStage(stage));
}
void	GameManager::ChangeBGM(LPDIRECTSOUNDBUFFER pBuffer)
{
	if (m_bgmBuffer != NULL)
	{
		
		dsMgr.stopSound(m_bgmBuffer);
	}
	m_bgmBuffer	 = pBuffer;			
	if (m_bgmBuffer != NULL)
	{
		dsMgr.playSoundLoop(m_bgmBuffer);
	}
}

void	GameManager::ChangeState(DWORD state)
{	
	switch(state)
	{
	case GAME_STATE_CHAT:
		m_stateElapsedFrame = 0;
		//LoadChatText
		
		break;

	}
	m_state = state;
}