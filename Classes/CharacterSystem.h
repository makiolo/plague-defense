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
#include "PhysicsBoxComponent.h"
#include "IntrospectionComponent.h"
#include "GravityComponent.h"

namespace plague {

struct CharacterSystem : public entityx::System<CharacterSystem>, public entityx::Receiver<CharacterSystem>
{
	explicit CharacterSystem()
		: _left(false)
		, _right(false)
		, _fire(false)
		, _projectil_total(0)
	{
		;
	}

	virtual ~CharacterSystem()
	{

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
		projectil.assign<plague::PhysicsDescription>();
		projectil.assign<plague::PhysicsIntrospectionComponent>();
		projectil.assign<plague::GravityComponent>(400, 300);
		projectil.assign<plague::AutoDestroyDescription>(0.7f);
		plague::make_sprite(projectil, scene, "img/character/piedra.png", spawn_point, 0.2f);
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
	    /*
		_projectil_total = 0;
		es.each<plague::Transform, plague::ProjectilComponent>([&](entityx::Entity entity, plague::Transform& transform, plague::ProjectilComponent& projectil) {
			++_projectil_total;
		});
	    */

		es.each<plague::Transform, plague::CharacterComponent>([=, &es, &events](entityx::Entity entity, plague::Transform& transform, plague::CharacterComponent& character)
		{
			const float velocity = character.velocity;
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

			if(position.x <= 0)
				position.x = 0;

			if(position.x >= 1080)
				position.x = 1080;

			if (_left || _right)
			{
				transform.node->setPosition(position);
				transform.node->setScaleX(scale_x);
			}

			if (_fire)
			{
				spwan_projectil(es, events, position + cocos2d::Vec2(0, -60));
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
	int _projectil_total;
};

}

#endif

