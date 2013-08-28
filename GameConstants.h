//--------------------------------------------------------------------------------------
//File: GameConstants.h
//
//Desc: Define global constants and enum types used in the Game
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H
#include <windows.h>
//--------------------------------------------------------------------------------------
//Active rect 
//--------------------------------------------------------------------------------------
#define ACTIVE_RECT_LEFT		32
#define ACTIVE_RECT_TOP			32
#define ACTIVE_RECT_RIGHT		424
#define ACTIVE_RECT_BOTTOM		496
#define ACTIVE_RECT_WIDTH		(ACTIVE_RECT_RIGHT - ACTIVE_RECT_LEFT)
#define ACTIVE_RECT_HEIGHT		(ACTIVE_RECT_BOTTOM - ACTIVE_RECT_TOP)
#define ACTIVE_RECT_CENTER_X	(ACTIVE_RECT_LEFT + ACTIVE_RECT_WIDTH / 2)
#define ACTIVE_RECT_CENTER_Y	(ACTIVE_RECT_TOP + ACTIVE_RECT_HEIGHT / 2)
#define	MAX_POINT_LINE			128		//ALSO ITEM COLLECT BORDER

#define	TEXTURE_NUM				35
#define SOUND_NUM				26
#define BGM_NUM					5
//--------------------------------------------------------------------------------------
//Texture files
//--------------------------------------------------------------------------------------

enum  TextureType { TEXTURE_MUSICBG, TEXTURE_MUSIC, TEXTURE_RESULTBG, TEXTURE_SELECTBG, TEXTURE_STAFF, TEXTURE_LOGO, TEXTURE_TITLE,
					TEXTURE_TITLE_01, TEXTURE_TITLE_01S,TEXTURE_TITLE_02, TEXTURE_TITLE_03,
					TEXTURE_ASCII, TEXTURE_ASCII_S, TEXTURE_EFF_00, TEXTURE_EFF_01, TEXTURE_EFF_02, TEXTURE_EFF_03,
					TEXTURE_EFF_04, TEXTURE_EFF_05, TEXTURE_EFF_06, TEXTURE_EFF_07, TEXTURE_BULLET1, TEXTURE_BULLET2,
					TEXTURE_FRONT, TEXTURE_LOADING, TEXTURE_PLAYER_00,TEXTURE_PLAYER_01,TEXTURE_REPLAY,TEXTRE_RESULT,
					//TEXTURE_RESULT_01, TEXTURE_RESULT_02, TEXTURE_RESULT_03, TEXTURE_SELECT_01,TEXTURE_SELECT_02,TEXTURE_SELECT_03,
					//TEXTURE_SELECT_04,TEXTURE_SELECT_05,TEXTURE_PLAYER_SELECT
					TEXTURE_STG1BG, TEXTURE_STG1ENM,TEXTURE_STG1BOSS, TEXTURE_STG2BG, TEXTURE_STG2ENM, TEXTURE_STG2BOSS,
					};
const std::string TEXTURE_FILENAME[]	= {"music.jpg", "music00.dds", "result.jpg", "select00.jpg", "staff00.jpg", "th06logo.jpg", "title00.jpg",
										   "title01.dds", "title01s.dds", "title02.dds", "title03.dds",
										   "ascii.dds", "asciis.dds", "eff00.png", "eff01.png", "eff02.png", "eff03.png",
										   "eff04.png", "eff05.png",  "eff06.png", "eff07.png", "etama3.dds", "etama4.dds",
										   "front.dds", "loading.png", "player00.dds", "player01.dds", "replay00.dds", "result00.dds",
										   "stg1bg.dds", "stg1enm.dds", "stg1enm2.dds","stg2bg.png", "stg2enm.dds", "stg2enm2.dds",
										  };


const RECT TITLE_MENU_ITEM_RECT[] = {{0, 0, 72, 24},		//Start
									 {84, 0, 256, 24},		//Extra Start
									 {0, 192, 180, 216},	//Practice Start
									 {0, 36, 90, 60},		//Replay
									 {100, 36, 180, 56},	//Score
									 {100, 164, 256, 184},	//Music Room 
									 {0, 64, 90, 92},		//Option
									 {190, 36, 256, 60}};	//Quit

//--------------------------------------------------------------------------------------
//Sound files
//--------------------------------------------------------------------------------------
enum  SoundType { SOUND_CANCEL = 0, SOUND_CAT, SOUND_DAMAGE, SOUND_ENEP,SOUND_ENEP_01, SOUND_EXTEND, SOUND_GRAZE, 
				  SOUND_GUN, SOUND_ITEM, SOUND_KIRA, SOUND_KIRA_01, SOUND_KIRA_02, SOUND_LAZER, SOUND_LAZER_01,
				  SOUND_NEP, SOUND_OK, SOUND_PLDEAD, SOUND_PLST, SOUND_POWER, SOUND_POWER_1, SOUND_POWERUP, 
				  SOUND_SELECT, SOUND_TAN, SOUND_TAN_01, SOUND_TAN_02, SOUND_TIMEOUT};
const std::string SOUND_FILENAME[] = { "cancel00.wav", "cat00.wav", "damage00.wav", "enep00.wav", "enep01.wav", "extend.wav","graze.wav",
									   "gun00.wav", "item00.wav", "kira00.wav", "kira01.wav", "kira02.wav", "lazer00.wav", "lazer01.wav",
									   "nep00.wav", "ok00.wav", "pldead00.wav", "plst00.wav", "power0.wav", "power1.wav", "powerup.wav",
									   "select00.wav", "tan00.wav", "tan01.wav", "tan02.wav", "timeout.wav"};
enum  BGMType	{ BGM_TITLE	= 0, BGM_STG1, BGM_STG1BOSS, BGM_STG2, BGM_STG2BOSS};
const std::string BGM_FILENAME[]	= {"th06_01.wav", "th06_02.wav", "th06_03.wav", "th06_04.wav", "th06_05.wav"};
const std::string BGM_PATH		=   "./BGM/";
const std::string SOUND_PATH	=	"./music/";
const std::string TEXTURE_PATH	=	"./img/";
//--------------------------------------------------------------------------------------
//Collision type
//--------------------------------------------------------------------------------------
typedef enum _COLLISIONTYPE{
	COLLISION_RECT						= 1,
	COLLISION_CIRCLE					= 2,
	COLLISION_ELLIPSE					= 3,
	COLLISION_TRIANGLE					= 4,
} COLLISIONTYPE;
//--------------------------------------------------------------------------------------
//Delete Macro
//--------------------------------------------------------------------------------------
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif

#define NULL_POSITION D3DXVECTOR2(0, 0)
#endif