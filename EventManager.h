//--------------------------------------------------------------------------------------
//File: EventManager.h
//      Hold a list of all resisted callbacks for each event type.
//		
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#ifndef EVENT_MANAGE_H
#define EVENT_MANAGE_H
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
#include "FastDelegate.h"
const static int EVENT_TYPE_NUM = 2;
enum EventType 
{
	EVENT_TYPE_ITEM_COLLECTED,			// 0
	EVENT_TYPE_ENYMY_ELIMINATED,		// 1
};

/************************************************************************/
/* Record useful eventArgs including sender                                                                     
/************************************************************************/
class EventArgs
{
};

typedef fastdelegate::FastDelegate1<EventArgs*, void> Callback;

class EventManager
{
public:
	static	void AddListener(EventType, Callback);
	static  void RemoveListener(EventType, Callback);
	static  void Broadcast(EventType, EventArgs*);
private:
	static std::list<Callback> eventTable[EVENT_TYPE_NUM];
};

#endif