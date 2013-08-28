//--------------------------------------------------------------------------------------
//File: GameObject.h
//
//Desc: The base class ,describes an object that will be rendered in the game.
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include <d3dx9.h>
#include <vector>
#include "GameConstants.h"
#include "GameSprite.h"
#include "MotionTrack.h"
#include "Collision.h"
#include "./dxutil/TextRender.h"
//--------------------------------------------------------------------------------------
//Forward Declarations
//--------------------------------------------------------------------------------------
typedef struct MotionInfo
{
	MotionInfo(int frame, MotionTrack * pTrack, bool bIsRuntimeOffset = false, GameObject *pTarget = NULL, D3DXVECTOR2 targetOffset = NULL_POSITION, bool bIsKeepTrack = false)
	{
		this->keyFrame		= frame;
		this->pTrack		= pTrack;
		this->bIsRuntimeOffset = bIsRuntimeOffset;
		this->pTarget		= pTarget;
		this->targetOffset  = targetOffset;
		if (bIsRuntimeOffset)
			this->pTrack->SetOffset(D3DXVECTOR2(0, 0));
		this->bIsKeepTrack = bIsKeepTrack;
	}
	~MotionInfo()
	{
		SAFE_DELETE(pTrack);
	}
	int				keyFrame;
	MotionTrack *   pTrack;
	bool			bIsRuntimeOffset;
	GameObject*		pTarget;
	D3DXVECTOR2		targetOffset;
	bool			bIsKeepTrack;

} MotionInfo;

class GameObject
{
public:
	//--------------------------------------------------------------------------------------
	// Initialize
	//--------------------------------------------------------------------------------------
					GameObject(TextureType textureType, MotionInfo *pInfo = NULL, 
								COLLISIONTYPE collisionType = COLLISION_RECT, const D3DXVECTOR2 &scaleMatrix = D3DXVECTOR2(1,1),
								float rotation = 0);
					~GameObject();
	void			Init();
	//--------------------------------------------------------------------------------------
	//	Getter && Setter
	//--------------------------------------------------------------------------------------
	//Position
	void			SetPosition(float x, float y)		{ m_position.x = x ; m_position.y = y;}
	void			SetPosition(const D3DXVECTOR2 &newPosition){ m_position = newPosition;}
	D3DXVECTOR2		GetPosition(void)	const			{ return m_position; }
	void			SetCenter(const D3DXVECTOR2 &newPosition)  { m_position.x = newPosition.x - m_width / 2.0f; m_position.y = newPosition.y - m_height / 2.0f;}
	D3DXVECTOR2		GetCenter(void)		const			{ return D3DXVECTOR2(m_position.x + m_width / 2, m_position.y + m_height / 2); }
	//Motion
	//void			SetSpeed(float newV)				{ m_v = newV;}
//	float			GetSpeed(void)		const			{ return m_v;}
//	void			SetAccelerate(float a)				{ m_a = a;}
//	float			GetAccelerate(void)	const			{ return m_a;}
	void			SetDirection(float theta);
	void			SetDirection(float x,float y);
	void			SetDirection(const D3DXVECTOR2 &direction);
	D3DXVECTOR2		GetDirection(void) const			{ return m_direction;}
	RECT			GetRect(void)	const;

	void			SetSprite(RECT &srcRect, int numFrames, int frameInterval,int width, int height,  bool loop = true); 
	GameSprite *	GetGameSprite(void)	const			{ return m_pSprite;}
	//screen is defined according to ACTIVE_RECT defined in GameManager.h
	bool			IsInScreen();	
	bool			IsValid()							{ return m_bIsValid;}
	void			SetValid(bool valid)				{ m_bIsValid = valid;}
	void			SetColor(int alpha)					{ m_color = D3DCOLOR_ARGB(alpha, 255, 255, 255);}
	void			SetColor(D3DCOLOR color)			{ m_color = color;}
	void			SetTextureType(TextureType type)	{ m_textureType = type;}
	int	GetElapsedFrame(void)	const					{ return m_elapsedFrame;}
	void			SetMaxLifeTime(unsigned int time)	{ m_maxLifeTime = time;}
	void			SetScaleMatrix(float x, float y)	{ m_scaleMatrix.x = x; m_scaleMatrix.y = y;}
	CollisionInfo * GetCollisionInfo(void)	const		{ return m_pCollisionInfo;}
	void			SetCollisionInfo(CollisionInfo *info){if (m_pCollisionInfo != NULL) delete m_pCollisionInfo; m_pCollisionInfo = info;}
	COLLISIONTYPE	GetCollisionType(void)	const		{ return m_collisionType;}
	void			SetCollisionType(COLLISIONTYPE type){ m_collisionType = type;}
	void			SetRotationAngle(float angle)		{ m_rotation	= angle;}
	MotionInfo*		GetMotionInfo(void) const			{ return m_pMotionInfo;}
	//--------------------------------------------------------------------------------------
	// Events
	//--------------------------------------------------------------------------------------
	virtual void	Update(void);
	virtual void	AutoUpdatePosition(void);
	virtual void	Render(ID3DXSprite * pSprite );
	//--------------------------------------------------------------------------------------
	//Called when the object is wipped in the game.
	//--------------------------------------------------------------------------------------
	virtual void	OnWipped(void);
	virtual bool	Collision(GameObject * pObject);
	
	void			ClearMotionInfo(void);
	int										motionIndex;
	std::vector<MotionInfo*>				motionInfos;
protected:
	GameSprite	*		m_pSprite;				//pointer to GameSprite, used to render object
	bool				m_bIsValid;				//valid flag
	D3DCOLOR			m_color;
	D3DXVECTOR2			m_position;				//current position
	D3DXVECTOR2			m_direction;			//speed direction
	float				m_v;					//speed
	float				m_a;					//accelarate
	int					m_width;
	int					m_height;
	int					m_elapsedFrame;			//shows how many frames since this object has been create
	int					m_maxLifeTime;
	TextureType			m_textureType;

	D3DXVECTOR2			m_scaleMatrix;
	float				m_rotation;				//rotation angle

	MotionInfo*			m_pMotionInfo;			//point to current motion info
	CollisionInfo *		m_pCollisionInfo;
	COLLISIONTYPE		m_collisionType;

};