/* System/Receiver class PhysicsSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _PhysicsSystem_H_
#define _PhysicsSystem_H_

#include <vector>
#include <tuple>
#include <cocos2d.h>
#include <physics/CCPhysicsWorld.h>
#include <physics/CCPhysicsBody.h>
#include <physics3d/CCPhysics3DWorld.h>
#include "entityx/entityx.h"
#include "DebugPhysicsCommand.h"
#include "IntrospectionComponent.h"
#include "AutoDestroy.h"
#include "PhysicsBoxSystem.h"
#include "InsectDeadEvent.h"
#include "ProjectilComponent.h"
#include "GravityComponent.h"

namespace plague {

struct PhysicsSystem : public entityx::System<PhysicsSystem>, public entityx::Receiver<PhysicsSystem>
{
	explicit PhysicsSystem(cocos2d::Scene* scene)
		: _scene(scene)
	{
		/*
		A PhysicsBody holds the physical properties of an object. These include mass, position, rotation, velocity and damping.
		PhysicsBody objects are the backbone for shapes. A PhysicsBody does not have a shape until you attach a shape to it.
		*/
		_scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
		_scene->getPhysicsWorld()->setAutoStep(false);
		_scene->getPhysicsWorld()->setSubsteps(3);

		_listener = cocos2d::EventListenerPhysicsContact::create();
		_listener->onContactBegin = CC_CALLBACK_1(PhysicsSystem::onContactBegin, this);
		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, _scene);
	}

	virtual ~PhysicsSystem()
	{
		_scene->getEventDispatcher()->removeEventListener(_listener);
		CC_SAFE_RELEASE_NULL(_listener);
	}

	bool onContactBegin(cocos2d::PhysicsContact& contact)
	{
		auto shapeA = contact.getShapeA();
		auto shapeB = contact.getShapeB();

		auto bodyA = contact.getShapeA()->getBody();
		auto bodyB = contact.getShapeB()->getBody();

		auto nodeA = bodyA->getNode();
		auto nodeB = bodyB->getNode();

		PhysicsBoxSystem::update_collision_bitmask(bodyA, DEAD);
		PhysicsBoxSystem::update_collision_bitmask(bodyB, DEAD);

		plague::IntrospectionComponent* objA = (plague::IntrospectionComponent*)nodeA->getUserData();
		plague::IntrospectionComponent* objB = (plague::IntrospectionComponent*)nodeB->getUserData();

		_destroy.push_back(std::make_tuple(objA->id, objB->id));

 		return true;
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		events.subscribe<plague::DebugPhysicsCommand>(*this);
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		_scene->getPhysicsWorld()->step(dt);

		if (_destroy.size() > 0)
		{
			for (auto& tuple : _destroy)
			{
				entityx::Entity::Id idA, idB;
				std::tie(idA, idB) = tuple;
				auto projectile = es.get(idA);
				auto insect = es.get(idB);
#if 1
				if (!insect.has_component<plague::AutoDestroy>() && !insect.has_component<plague::GravityComponent>() && insect.has_component<plague::InsectComponent>() && (projectile != insect))
				{
					auto gravity_component = projectile.component<plague::GravityComponent>().get();
					insect.assign<plague::GravityComponent>(gravity_component->vel, gravity_component->acc);

					auto transform_component = insect.component<plague::Transform>().get();
					transform_component->node->setScaleY(transform_component->node->getScaleY() * -1);

					auto sprite_component = insect.component<plague::Sprite>().get();
					sprite_component->sprite->stopAllActions();

					events.emit<plague::InsectDeadEvent>();
				}
#else
				if (!insect.has_component<plague::AutoDestroy>() && insect.has_component<plague::InsectComponent>())
				{
					insect.assign<plague::AutoDestroy>();
					events.emit<plague::InsectDeadEvent>();
				}
#endif
			}
			_destroy.clear();
		}
	}

	void receive(const plague::DebugPhysicsCommand& command)
	{
		
	}

protected:
	cocos2d::Scene* _scene;
	cocos2d::EventListenerPhysicsContact* _listener;
	std::vector<std::tuple<entityx::Entity::Id, entityx::Entity::Id> > _destroy;
};

}

#endif
