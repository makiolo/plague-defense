/* System class PhysicsBoxSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _PhysicsBoxSystem_H_
#define _PhysicsBoxSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Sprite.h"
#include "PhysicsBoxComponent.h"
#include "IntrospectionComponent.h"

namespace plague {

enum PhysicsMask {
	DYNAMIC = 0x01,
	STATIC = 0x02,
	DEAD = 0x03,
};

struct PhysicsBoxSystem : public entityx::System<PhysicsBoxSystem>
{
	explicit PhysicsBoxSystem()
	{
		
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		
	}

	static void update_collision_bitmask(cocos2d::PhysicsBody* body, PhysicsMask mask)
	{
		if (mask == DYNAMIC)
		{
			body->setCategoryBitmask(DYNAMIC);
			body->setCollisionBitmask(0xFFFFFFFF & (~DYNAMIC | ~DEAD));
			body->setContactTestBitmask(0xFFFFFFFF & (~DYNAMIC | ~DEAD));
		}
		else if(mask == STATIC)
		{
			body->setCategoryBitmask(STATIC);
			body->setCollisionBitmask(0xFFFFFFFF & (~STATIC | ~DEAD));
			body->setContactTestBitmask(0xFFFFFFFF & (~STATIC | ~DEAD));
		}
		else if (mask == DEAD)
		{
			body->setCategoryBitmask(DEAD);
			body->setCollisionBitmask(0xFFFFFFFF & (~STATIC | ~DYNAMIC | ~DEAD));
			body->setContactTestBitmask(0xFFFFFFFF & (~STATIC | ~DYNAMIC | ~DEAD));
		}
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Sprite, plague::PhysicsBoxComponent, plague::IntrospectionComponent>([=](entityx::Entity entity, plague::Sprite& sprite, plague::PhysicsBoxComponent& physics, plague::IntrospectionComponent& introspection) {

			auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(sprite.sprite->getContentSize().width, sprite.sprite->getContentSize().height), cocos2d::PhysicsMaterial(physics.density, physics.restitution, physics.friction));
			physicsBody->setDynamic(false);
			update_collision_bitmask(physicsBody, physics.dynamic ? DYNAMIC : STATIC);

			//apply physicsBody to the sprite
			sprite.sprite->setPhysicsBody(physicsBody);

			// set introespection Id
			introspection.id = entity.id();
			physicsBody->getNode()->setUserData((void*)&introspection);

			entity.component<plague::PhysicsBoxComponent>().remove();
		});
	}
};

}

#endif
