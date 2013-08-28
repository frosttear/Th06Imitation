//--------------------------------------------------------------------------------------
//File: GameObject.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "GameObject.h"
#include "GameManager.h"

GameObject::GameObject(TextureType textureType, MotionInfo *pInfo, COLLISIONTYPE collisionType, const D3DXVECTOR2 &scaleMatrix, float rotation) 
{
	Init();
	m_textureType		= textureType;
	m_pMotionInfo		= pInfo;
	if (pInfo != NULL)
	{
		motionInfos.push_back(pInfo);
		if (pInfo->pTrack != NULL)
			m_position		 = pInfo->pTrack->GetOffset();
	}
	motionIndex		= 0;
	m_collisionType		= collisionType;
	m_scaleMatrix		= scaleMatrix;
	m_rotation			= rotation;
	m_pCollisionInfo	= NULL;

}

GameObject::~GameObject()
{
	if (m_pSprite != NULL)
		delete m_pSprite;
	m_pSprite = NULL;
	ClearMotionInfo();
	m_pMotionInfo  = NULL;
	SAFE_DELETE(m_pCollisionInfo);
}
//--------------------------------------------------------------------------------------
//Init GameObject, ready to be reused
//--------------------------------------------------------------------------------------
void GameObject::Init()
{
	m_bIsValid			= true;
	m_pSprite			= NULL;
	m_elapsedFrame		= 0;
	m_maxLifeTime		= 0;
	m_v					= 0;
	m_a					= 0;
	m_color				= D3DCOLOR_ARGB(255,255,255,255);
	m_position.x		= 0;
	m_position.y		= 0;
}
RECT	GameObject::GetRect() const
{
	RECT rect;
	SetRect(&rect, (int)m_position.x,(int) m_position.y ,(int) m_position.x + m_width, (int)m_position.y + m_height);
	return rect;
}

void	GameObject::SetSprite(RECT &srcRect, int numFrames, int frameInterval, 
					   int width, int height, bool loop)
{
	m_width		= width;
	m_height	= height;
	if (m_pSprite == NULL) 
	{
		m_pSprite = new GameSprite(srcRect, numFrames, frameInterval, width, height, loop);
	}else
	{
		m_pSprite->Set(srcRect, numFrames, frameInterval, width, height, loop);
	}
}

void	GameObject::SetDirection(float x, float y)
{
	float length = sqrt(x * x + y * y);
	if (abs(length) > 0.000000001)
	{
		m_direction.x = x / length;
		m_direction.y = y / length;
	}else
	{
		m_direction.x = 0;
		m_direction.y = 0;
	}

}

void	GameObject::SetDirection(const D3DXVECTOR2 &direction)
{
	SetDirection(direction.x, direction.y);
}

void	GameObject::SetDirection(float theta)
{
	m_direction.x = cos(theta);
	m_direction.y = sin(theta);
}
//--------------------------------------------------------------------------------------
// DESC: Update position
//--------------------------------------------------------------------------------------
void	GameObject::Update()
{
	if (motionInfos.size() > 0)
		AutoUpdatePosition();
	++m_elapsedFrame;
	//check valid
	if ((m_maxLifeTime > 0 && m_elapsedFrame > m_maxLifeTime) || !IsInScreen())
		m_bIsValid = false;

}
//--------------------------------------------------------------------------------------
//AutoUpdatePosition: update position according to motionInfos, *motionIterator 
//point to the next key frame's motionInfo
//--------------------------------------------------------------------------------------
void	GameObject::AutoUpdatePosition(void)
{
	int size = (unsigned int)motionInfos.size();
	//reach next key frame, if necessary, set next track's init position to current position
	if (size > 0 && motionIndex < size && m_elapsedFrame == motionInfos[motionIndex]->keyFrame)
	{
		m_pMotionInfo = motionInfos[motionIndex];
		if (m_pMotionInfo != NULL && m_pMotionInfo->pTrack != NULL)
		{
			if (m_pMotionInfo->bIsRuntimeOffset)
			{
				m_pMotionInfo->pTrack->SetOffset(m_position - m_pMotionInfo->pTrack->GetRelativePosition((float)m_elapsedFrame));
			}
			if (m_pMotionInfo->pTarget != NULL)
			{
				m_pMotionInfo->pTrack->SetDirection(m_pMotionInfo->pTarget->GetCenter() - this->GetCenter() + m_pMotionInfo->targetOffset);
			}
		}
		++ motionIndex;
	}
	if (m_pMotionInfo != NULL)
	{
		MotionTrack * pTrack = m_pMotionInfo->pTrack;
		
		if (pTrack != NULL)
			pTrack->Move(this, (float)m_elapsedFrame);

		//modify direction and t0 to keep track
		if (m_pMotionInfo->pTarget != NULL && m_pMotionInfo->bIsKeepTrack)
		{
			
				pTrack->SetT0((float)m_elapsedFrame);
				pTrack->SetDirection(m_pMotionInfo->pTarget->GetCenter() - this->GetCenter() + m_pMotionInfo->targetOffset);
				pTrack->SetOffset(this->GetCenter());
			
		}
		
	}
	
}
//--------------------------------------------------------------------------------------
// DESC: Render ,
//--------------------------------------------------------------------------------------
void	GameObject::Render(ID3DXSprite * pSprite)
{
	D3DXMATRIX transMatrix;
	D3DXVECTOR2 centerVector(m_width * 0.5f , m_height * 0.5f);
	D3DXMatrixTransformation2D(&transMatrix, &centerVector, 0.0f,&m_scaleMatrix, &centerVector, m_rotation, &m_position);
	pSprite->SetTransform(&transMatrix);
	m_pSprite->Render(pSprite, rm.GetTexture(m_textureType), m_color);
}
//--------------------------------------------------------------------------------------
// DESC: Called when this object is invalid,to do something after be wipped
//--------------------------------------------------------------------------------------
void	GameObject::OnWipped()
{
}

bool	GameObject::IsInScreen()
{
	if (m_position.x > ACTIVE_RECT_RIGHT 
		|| m_position.x < ACTIVE_RECT_LEFT - m_width 
		|| m_position.y > ACTIVE_RECT_BOTTOM 
		|| m_position.y < ACTIVE_RECT_TOP - m_height)
		return false;
	return true;
}

bool GameObject::Collision(GameObject * pObject)
{
	return Collision::CollisionRect(&this->GetRect(), &pObject->GetRect());	
}

void	GameObject::ClearMotionInfo(void)
{	
	for (int i = (unsigned int)motionInfos.size() - 1; i >=  0; --i)
	{
		MotionInfo* pInfo = motionInfos[i];
		motionInfos.pop_back();
		SAFE_DELETE(pInfo);
	}
}