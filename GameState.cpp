////--------------------------------------------------------------------------------------    
////File		:  GameState.cpp
////Path		:  D:\MYPROJECTS\TH06-LIKE\TH06-LIKE\
////Author    :  Liu.zhenxing
////CreateTime:  2010/9/15 11:00
////Desc		:  
////--------------------------------------------------------------------------------------
//#include "GameState.h"
//#include "GameManager.h"
//GameState::GameState(LPDIRECT3DTEXTURE9 pBackground, LPDIRECTSOUNDBUFFER pBgmBuffer)
//{
//	m_elapsedFrame	= 0;
//	m_pBackground	= pBackground;
//	m_pBgmBuffer	= pBgmBuffer;
//}
//
//void GameState::Update(void)
//{
//	++m_elapsedFrame;
//}
//
//GameStateBattle::GameStateBattle(LPDIRECT3DDEVICE9 pBackground, LPDIRECTSOUNDBUFFER pBgmBuffer)
//				:GameState(pBackground, pBgmBuffer)
//{
//
//}
//
//void GameStateBattle::Render()
//{
//	gm.RenderBattleScene();
//}
//
//void GameStateBattle::Update()
//{
//	GameState::Update();
//	gm.GameStateRun();
//
//}