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
#include "ProjectilComponent.h"
#include "PhysicsBoxComponent.h"
#include "IntrospectionComponent.h"
#include "GravityComponent.h"
#include "Level01Constants.h"

namespace plague {

struct CharacterSystem : public entityx::System<CharacterSystem>
{
	explicit CharacterSystem()
	{
		;
	}

	virtual ~CharacterSystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		es.each<plague::Transform, plague::CharacterComponent>([=, &es, &events](entityx::Entity entity, plague::Transform& transform, plague::CharacterComponent& character)
		{
			character.configure(es, events);
		});
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::CharacterComponent>([=, &es, &events](entityx::Entity entity, plague::Transform& transform, plague::CharacterComponent& character)
		{
			const float velocity = character.velocity;
			cocos2d::Vec2 position = transform.node->getPosition();
			float scale_x = abs(transform.node->getScaleX());

			if (character._left)
			{
				position.x -= velocity * dt;
			}

			if (character._right)
			{
				position.x += velocity * dt;
				scale_x *= -1;
			}

			if(position.x <= level01::left_limit.x)
				position.x = level01::left_limit.x;

			if(position.x >= level01::right_limit.x)
				position.x = level01::right_limit.x;

			if (character._left || character._right)
			{
				transform.node->setPosition(position);
				transform.node->setScaleX(scale_x);
			}

			if (character._fire)
			{
				spwan_projectil(es, events, position + cocos2d::Vec2(0, -20));
				character._fire = false;
			}
		});	
	}

	void spwan_projectil(entityx::EntityManager& es, entityx::EventManager& events, cocos2d::Vec2 spawn_point)
	{
		cocos2d::Scene* scene = cocos2d::Director::getInstance()->getRunningScene();
		entityx::Entity projectil = es.create();
		projectil.assign<plague::ProjectilComponent>();
		projectil.assign<plague::PhysicsDescription>();
		projectil.assign<plague::PhysicsIntrospectionComponent>();
		projectil.assign<plague::GravityComponent>(400, 300);
		plague::make_sprite(projectil, scene, "img/character/piedra.png", spawn_point, 0.2f);
	}

};

}

#endif

