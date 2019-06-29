/* System/Receiver class CharacterSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CharacterSystem_H_
#define _CharacterSystem_H_

#include <cstdlib>
#include <cocos2d.h>
#include "entityx/entityx.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "FireCommand.h"
#include "ProjectilComponent.h"
#include "GravityComponent.h"

namespace plague {

struct CharacterSystem : public entityx::System<CharacterSystem>, public entityx::Receiver<CharacterSystem>
{
	explicit CharacterSystem()
		: _left(false)
		, _right(false)
		, _fire(false)
	{
		;
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		events.subscribe<plague::LeftCommand>(*this);
		events.subscribe<plague::RightCommand>(*this);
		events.subscribe<plague::FireCommand>(*this);
	}

	void spwan_projectil(entityx::EntityManager& es, entityx::EventManager& events, cocos2d::Vec2 spawn_point)
	{
		cocos2d::Scene* scene = cocos2d::Director::getInstance()->getRunningScene();
		entityx::Entity projectil = es.create();
		projectil.assign<plague::ProjectilComponent>();		
		projectil.assign<plague::GravityComponent>(200, 200);
		plague::make_sprite(projectil, scene, "img/character/piedra.jpg", spawn_point, 0.1f);
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::CharacterComponent>([=, &es, &events](entityx::Entity entity, plague::Transform& transform, plague::CharacterComponent& character)
		{
			float velocity = character.velocity;
			cocos2d::Vec2 position = transform.node->getPosition();
			float scale_x = abs(transform.node->getScaleX());

			if (_left)
			{
				position.x -= velocity * dt;
			}

			if (_right)
			{
				position.x += velocity * dt;
				scale_x *= -1;
			}

			if(position.x <= 488)
				position.x = 488;

			if(position.x >= 1228)
				position.x = 1228;

			if (_left || _right)
			{
				transform.node->setPosition(position);
				transform.node->setScaleX(scale_x);
			}

			if (_fire)
			{
				spwan_projectil(es, events, position);
				_fire = false;
			}
		});	
	}

	void receive(const plague::LeftCommand& event)
	{
		_left = event.active;	
	}

	void receive(const plague::RightCommand& event)
	{
		_right = event.active;
	}

	void receive(const plague::FireCommand& event)
	{
		_fire = true;
	}
protected:
	bool _left;
	bool _right;
	bool _fire;
};

}

#endif

