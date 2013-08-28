//--------------------------------------------------------------------------------------
//File: EventManager.cpp
//      Hold a list of all resisted callbacks for each event type.
//		Implements of each method
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "EventManager.h"

std::list<Callback> EventManager::eventTable[EVENT_TYPE_NUM];


void EventManager::AddListener(EventType type, Callback callback)
{
	eventTable[type].push_back(callback);
}

void EventManager::RemoveListener(EventType type, Callback callback)
{	
	std::list<Callback>::iterator iter = eventTable[type].begin();
	for (; iter != eventTable[type].end(); )
	{
		if (*iter == callback)
		{
			iter = eventTable[type].erase(iter);
		}else
		{
			++iter;
		}
	}
}

void EventManager::Broadcast(EventType type, EventArgs* args)
{
	for (std::list<Callback>::iterator iter = eventTable[type].begin(); iter != eventTable[type].end(); ++iter)
	{
		(*iter)(args);
	}
}

