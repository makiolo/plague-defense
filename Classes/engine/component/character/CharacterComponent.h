/* Component class CharacterComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CharacterComponent_H_
#define _CharacterComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/event/character/LeftCommand.h"
#include "engine/event/character/RightCommand.h"
#include "engine/event/character/FireCommand.h"
#include "engine/component/2d/SpriterModelComponent.h"

namespace plague {

struct CharacterComponent : public entityx::Component<CharacterComponent>, public entityx::Receiver<CharacterComponent>
{
	explicit CharacterComponent(entityx::Entity::Id whoami, float velocity_, bool invert_left_ = true)
		: _whoami(whoami)
		, velocity(velocity_)
		, _left(false)
		, _right(false)
		, _fire(false)
		, spriter(nullptr)
		, invert_left(invert_left_)
	{
		
	}

	virtual ~CharacterComponent()
	{
		
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events)
	{
		events.subscribe<plague::LeftCommand>(*this);
		events.subscribe<plague::RightCommand>(*this);
		events.subscribe<plague::FireCommand>(*this);
		// spriter = &spriter_;
	}

	void play(const std::string& name)
	{
		if(spriter)
		{
			spriter->entity->setCurrentAnimation(name);
		}
	}

	void receive(const plague::LeftCommand& event)
	{
		if (event.to == _whoami)
		{
			_left = event.active;
		}
	}

	void receive(const plague::RightCommand& event)
	{
		if (event.to == _whoami)
		{
			_right = event.active;
		}
	}

	void receive(const plague::FireCommand& event)
	{
		if (event.to == _whoami)
		{
			_fire = true;
		}
	}

	void setSpriter(SpriterModelComponent* s)
    {
	    spriter = s;
    }

	entityx::Entity::Id _whoami;
	SpriterModelComponent* spriter;
	float velocity;
	bool _left;
	bool _right;
	bool _fire;
	bool invert_left;
};

}

#endif
