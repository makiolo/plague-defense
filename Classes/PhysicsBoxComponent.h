/* Component class PhysicsComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _PhysicsBoxComponent_H_
#define _PhysicsBoxComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Sprite.h"
#include "IntrospectionComponent.h"

namespace plague {
	
enum PhysicsMask {
	DYNAMIC = 0x01,
	STATIC = 0x02,
	DEAD = 0x03,
};

struct PhysicsDescription {
	explicit PhysicsDescription(bool dynamic_ = true, cocos2d::Vec2 velocity_ = cocos2d::Vec2::ZERO, float density_ = 1.0f, float restitution_ = 1.0f, float friction_ = 1.0f)
		: dynamic(dynamic_)
		, velocity(velocity_)
		, density(density_)
		, restitution(restitution_)
		, friction(friction_)
	{
		
	}

	/*
	Materials describe material attributes:
		-density: It is used to compute the mass properties of the parent body.
		-restitution: It is used to make objects bounce. The restitution value is usually set to be between 0 and 1. 0 means no bouncing while 1 means perfect bouncing.
		-friction: It is used to make objects slide along each other realistically.
	*/
	bool dynamic;
	cocos2d::Vec2 velocity;
	float density;
	float restitution;
	float friction;
	
};

struct PhysicsComponent {
	explicit PhysicsComponent(entityx::Entity::Id entity_id, plague::Sprite* sprite_, plague::PhysicsDescription* physics, plague::PhysicsIntrospectionComponent* introspection, bool is_projectil)
	{
		if (is_projectil)
		{
			// physicsBody = cocos2d::PhysicsBody::createBox(sprite_->sprite->getContentSize(), cocos2d::PhysicsMaterial(physics->density, physics->restitution, physics->friction));
			physicsBody = cocos2d::PhysicsBody::createCircle(sprite_->sprite->getContentSize().width / 2.0, cocos2d::PhysicsMaterial(physics->density, physics->restitution, physics->friction));
			update_collision_bitmask(DYNAMIC);
			
		}
		else
		{
			physicsBody = cocos2d::PhysicsBody::createCircle(sprite_->sprite->getContentSize().width / 2.0, cocos2d::PhysicsMaterial(physics->density, physics->restitution, physics->friction));
			update_collision_bitmask(STATIC);
		}
		physicsBody->retain();

		//apply physicsBody to the sprite
		sprite = sprite_->sprite;
		sprite->setPhysicsBody(physicsBody);

		// set introespection Id
		introspection->id = entity_id;
		if (is_projectil)
		{
			introspection->type = "projectil";
		}
		else
		{
			introspection->type = "insect";
		}
		physicsBody->getNode()->setUserData((void*)introspection);
	}

	~PhysicsComponent()
	{
		physicsBody->removeFromWorld();
		physicsBody->autorelease();
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
		}
		else if (mask == STATIC)
		{
			physicsBody->setCategoryBitmask(0xFFFFFFFF);
			physicsBody->setCollisionBitmask(0x00000000);
			physicsBody->setContactTestBitmask(0xFFFFFFFF);
			physicsBody->setDynamic(false);
			physicsBody->setMass(cocos2d::PHYSICS_INFINITY);
		}
	}

	cocos2d::PhysicsBody* physicsBody;
	cocos2d::Sprite* sprite;
};

}

#endif
