// struct EntityWillDestroyEvent
//
// Ricardo Marmolejo García 2019
//
// use: 
//
#pragma once
#ifndef _EntityWillDestroy_H_
#define _EntityWillDestroy_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct EntityWillDestroyEvent : public entityx::Event<EntityWillDestroyEvent>
{
	explicit EntityWillDestroyEvent(entityx::Entity::Id whodie_, float remaining_time_)
		: whodie(whodie_)
		, remaining_time(remaining_time_)
	{
		
	}

    ~EntityWillDestroyEvent()
    {

    }

	float remaining_time;
	entityx::Entity::Id whodie;
};

}

#endif
