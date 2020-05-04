/* Component class CharacterComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CharacterComponent_H_
#define _CharacterComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "FireCommand.h"

namespace plague {

struct CharacterComponent : public entityx::Component<CharacterComponent>, public entityx::Receiver<CharacterComponent>
{
	explicit CharacterComponent(entityx::Entity::Id whoami, float velocity_)
		: _whoami(whoami)
		, velocity(velocity_)
		, _left(false)
		, _right(false)
		, _fire(false)
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

	entityx::Entity::Id _whoami;
	float velocity;
	bool _left;
	bool _right;
	bool _fire;
};

}

#endif
