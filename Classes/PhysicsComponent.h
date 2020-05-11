/* Component class PhysicsComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _PhysicsComponent_H_
#define _PhysicsComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Sprite.h"
#include "PhysicsIntrospectionComponent.h"
#include "PhysicsDescription.h"
#include "Transform.h"
#include "PhysicsIntrospectionComponent.h"

namespace plague {
	
enum PhysicsMask {
	DYNAMIC = 0x01,
	STATIC = 0x02,
	DEAD = 0x03,  // TODO: unused
};

struct PhysicsComponent : public entityx::Component<PhysicsComponent>
{
	explicit PhysicsComponent(plague::Sprite& sprite, plague::PhysicsDescription& physics_desc)
		: physicsBody(cocos2d::PhysicsBody::createCircle(sprite.get()->getContentSize().width / 2.0, cocos2d::PhysicsMaterial(physics_desc.density, physics_desc.restitution, physics_desc.friction)))
		, configured(false)
	{
		physicsBody->retain();
	}

	~PhysicsComponent()
	{
		physicsBody->removeFromWorld();
		physicsBody->release();
	}

	cocos2d::PhysicsBody* get() const
	{
		return physicsBody;
	}

	void configure_fw(Transform& transform, PhysicsIntrospectionComponent& introspection)
	{
		if(!configured)
		{
			// physicsBody->autorelease();
			transform.get()->setPhysicsBody(physicsBody);
			transform.get()->setUserData((void*)&introspection);
			configured = true;
		}
	}

	void update_collision_bitmask(PhysicsMask mask)
	{
		if (mask == DYNAMIC)
		{
			physicsBody->setCategoryBitmask(0xFFFFFFFF);
			physicsBody->setCollisionBitmask(0x00000000);
			physicsBody->setContactTestBitmask(0xFFFFFFFF);
			physicsBody->setDynamic(true);
			physicsBody->setGravityEnable(true);
			physicsBody->setMass(10);
			physicsBody->setGroup(DYNAMIC);
		}
		else if (mask == STATIC)
		{
			physicsBody->setCategoryBitmask(0xFFFFFFFF);
			physicsBody->setCollisionBitmask(0x00000000);
			physicsBody->setContactTestBitmask(0xFFFFFFFF);
			physicsBody->setDynamic(false);
			physicsBody->setMass(cocos2d::PHYSICS_INFINITY);
			physicsBody->setGroup(STATIC);
		}
	}

	cocos2d::PhysicsBody* physicsBody;
	bool configured;
};

}

#endif
