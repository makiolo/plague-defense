/* Component class CharacterComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CharacterComponent_H_
#define _CharacterComponent_H_

#include <cocos2d.h>
#include <entityx/entityx.h>
#include <engine/interface/CharacterInterface.h>
#include <engine/event/character/LeftCommand.h>
#include <engine/event/character/RightCommand.h>
#include <engine/event/character/FireCommand.h>
#include <engine/component/2d/SpriterModelComponent.h>

namespace plague {

struct CharacterComponent : public entityx::Component<CharacterComponent>, public entityx::Receiver<CharacterComponent>, public plague::CharacterInterface
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

    void setSpriter(SpriterModelComponent* spriter_)
    {
        spriter = spriter_;
    }

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events)
	{
		events.subscribe<plague::LeftCommand>(*this);
		events.subscribe<plague::RightCommand>(*this);
		events.subscribe<plague::FireCommand>(*this);
	}

	void play(const std::string& name)
	{
		if(spriter)
		{
			spriter->entity->setCurrentAnimation(name);
		}
	}

	void left(bool active) override
    {
	    _left = active;
    }

    void right(bool active) override
    {
        _right = active;
    }

    void fire(bool active) override
    {
        _fire = active;
    }

	void receive(const plague::LeftCommand& event)
	{
		if (event.to == _whoami)
		{
			left(event.active);
		}
	}

	void receive(const plague::RightCommand& event)
	{
		if (event.to == _whoami)
		{
            right(event.active);
		}
	}

	void receive(const plague::FireCommand& event)
	{
		if (event.to == _whoami)
		{
            fire(true);
		}
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
