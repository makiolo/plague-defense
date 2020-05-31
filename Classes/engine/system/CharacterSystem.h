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
#include "engine/component/type/ProjectilComponent.h"
#include "engine/component/character/CharacterComponent.h"
#include "engine/component/PhysicsComponent.h"
#include "engine/component/type/PhysicsIntrospectionComponent.h"
#include "engine/component/StammableComponent.h"
#include "engine/scene/constants/Level01Constants.h"
#include "engine/component/SceneComponent.h"
#include "engine/component/2d/ParticleFireWorksComponent.h"
#include "engine/component/2d/SpriterModelComponent.h"

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
		es.each<plague::Transform, plague::CharacterComponent>([&](entityx::Entity entity, plague::Transform& transform, plague::CharacterComponent& character)
		{
			character.configure_fw(es, events);
		});
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::CharacterComponent>([&](entityx::Entity entity, plague::Transform& transform, plague::CharacterComponent& character)
		{
			const float velocity = character.velocity;
			cocos2d::Vec2 position = transform.get()->getPosition();
			float scale_x = abs(transform.get()->getScaleX());

			if (character._left)
			{
				position.x -= velocity * dt;
				if(character.invert_left) {
                    scale_x *= -1;
                }
			}

			if (character._right)
			{
				position.x += velocity * dt;
                if(!character.invert_left) {
                    scale_x *= -1;
                }
			}

			if(position.x <= level01::left_limit.x)
				position.x = level01::left_limit.x;

			if(position.x >= level01::right_limit.x)
				position.x = level01::right_limit.x;

			if (character._left || character._right)
			{
				transform.get()->setPosition(position);
				transform.get()->setScaleX(scale_x);
				character.play("walk");
			}
			else
			{
				character.play("idle");
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
		entityx::Entity projectil = es.create();
		// Hace que la entidad sea de tipo proyectil
		projectil.assign<plague::ProjectilComponent>();
		// Fisica
		projectil.assign<plague::PhysicsDescription>();
		projectil.assign<plague::PhysicsIntrospectionComponent>();
		// Hace que explote, en caso de colision 
		projectil.assign<plague::StammableComponent>();
		// Apariencia
		//
		cocos2d::Scene* scene = cocos2d::Director::getInstance()->getRunningScene();
		projectil.assign<plague::SceneComponent>(scene);
		projectil.assign<plague::Transform>(spawn_point, 0.2f);  // position and scale
		projectil.assign<plague::Sprite2DComponent>("img/character/piedra.png");
		// projectil.assign<plague::ParticleFireworksCompomnent>( projectil.id() );
	}

};

}

#endif

