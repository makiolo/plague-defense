// struct ProjectilInsectCollisionEvent
//
//
// Created by Ricardo Marmolejo García on 6/10/2020.
//
//
// use: 
//
#pragma once
#ifndef _ProjectilInsectCollisionEvent_H_
#define _ProjectilInsectCollisionEvent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct ProjectilInsectCollisionEvent : public entityx::Event<ProjectilInsectCollisionEvent>
{
	explicit ProjectilInsectCollisionEvent(entityx::Entity::Id projectil_, entityx::Entity::Id insect_)
	    : projectil(projectil_)
        , insect(insect_)
    {

	}

	~ProjectilInsectCollisionEvent()
    {

    }

	entityx::Entity::Id projectil;
    entityx::Entity::Id insect;
};

}

#endif //_ProjectilInsectCollisionEvent_H_