/* Component class PhysicsComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _PhysicsComponent_H_
#define _PhysicsComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/2d/Sprite2DComponent.h"
#include "engine/component/type/PhysicsIntrospectionComponent.h"
#include "engine/component/descriptor/PhysicsDescription.h"
#include "Transform.h"
#include "engine/component/type/PhysicsIntrospectionComponent.h"

namespace plague {
	
enum PhysicsMask {
	DYNAMIC = 0x01,
	STATIC = 0x02,
};

struct PhysicsComponent : public entityx::Component<PhysicsComponent>
{
	explicit PhysicsComponent(plague::Sprite2DComponent& sprite, plague::PhysicsDescription& physics_desc)
		: physics_body(cocos2d::PhysicsBody::createCircle(sprite.get()->getContentSize().width / 2.0, cocos2d::PhysicsMaterial(physics_desc.density, physics_desc.restitution, physics_desc.friction)))
		, configured(false)
	{
		physics_body->retain();
	}

	~PhysicsComponent()
	{
		physics_body->removeFromWorld();
		physics_body->release();
	}

	cocos2d::PhysicsBody* get() const
	{
		return physics_body;
	}

	void configure_fw(Transform& transform, PhysicsIntrospectionComponent& introspection)
	{
		if(!configured)
		{
			transform.get()->setPhysicsBody(physics_body);
			transform.get()->setUserData((void*)&introspection);
			configured = true;
		}
	}

	void update_collision_bitmask(PhysicsMask mask)
	{
        physics_body->setCategoryBitmask(0xFFFFFFFF);
        physics_body->setCollisionBitmask(0x00000000);
        physics_body->setContactTestBitmask(0xFFFFFFFF);
		if (mask == DYNAMIC)
		{
			physics_body->setDynamic(true);
			physics_body->setGravityEnable(true);
			physics_body->setMass(10);
			physics_body->setGroup(DYNAMIC);
		}
		else if (mask == STATIC)
		{
			physics_body->setDynamic(false);
			physics_body->setMass(cocos2d::PHYSICS_INFINITY);
			physics_body->setGroup(STATIC);
		}
	}

	cocos2d::PhysicsBody* physics_body;
	bool configured;
};

}

#endif
