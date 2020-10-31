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
#include <engine/event/collision/ProjectilInsectCollisionEvent.h>
#include "entityx/entityx.h"
#include "engine/component/type/PhysicsIntrospectionComponent.h"
#include "engine/component/descriptor/AutoDestroyDescription.h"
#include "engine/system/builder/PhysicsBuilderSystem.h"
#include "engine/event/InsectDeadEvent.h"
#include "engine/component/type/ProjectilComponent.h"
#include "engine/component/StammableComponent.h"

namespace plague {

struct PhysicsSystem : public entityx::System<PhysicsSystem>
{
	explicit PhysicsSystem(cocos2d::Scene* scene)
		: _scene(scene)
	{
		/*
		A PhysicsBody holds the physical properties of an object. These include mass, position, rotation, velocity and damping.
		PhysicsBody objects are the backbone for shapes. A PhysicsBody does not have a shape until you attach a shape to it.
		*/
		// _scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
		// _scene->getPhysicsWorld()->setAutoStep(false);
		_scene->getPhysicsWorld()->setSubsteps(4);
		_scene->getPhysicsWorld()->setGravity(cocos2d::Vec2(0, -1000));

		_listener = cocos2d::EventListenerPhysicsContactWithGroup::create(STATIC);
		_listener->onContactBegin = CC_CALLBACK_1(PhysicsSystem::onContactBegin, this);
		_listener->onContactPreSolve = CC_CALLBACK_2(PhysicsSystem::onContactPreSolve, this);
		_listener->onContactPostSolve = CC_CALLBACK_2(PhysicsSystem::onContactPostSolve, this);
		// _listener->setEnabled(false);

		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, _scene);
	}

	virtual ~PhysicsSystem()
	{
		_scene->getEventDispatcher()->removeEventListener(_listener);
	}

	bool onContactBegin(cocos2d::PhysicsContact& contact)
	{
		auto shapeA = contact.getShapeA();
		auto shapeB = contact.getShapeB();

		auto bodyA = shapeA->getBody();
		auto bodyB = shapeB->getBody();

		auto nodeA = bodyA->getNode();
		auto nodeB = bodyB->getNode();

		auto objA = static_cast<plague::PhysicsIntrospectionComponent*>(nodeA->getUserData());
		auto objB = static_cast<plague::PhysicsIntrospectionComponent*>(nodeB->getUserData());

		if (objA->type == "projectil" && objB->type == "insect")
		{
			_destroy.emplace_back(objA->id, objB->id);
			return false;
		}
		else if (objB->type == "projectil" && objA->type == "insect")
		{
			_destroy.emplace_back(objB->id, objA->id);
			return false;
		}
 		return false;
	}

	bool onContactPreSolve(cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)
	{

		return true;
	}

	void onContactPostSolve(cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
	{

	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		if (!_destroy.empty())
		{
			for (auto& tuple : _destroy)
			{
				entityx::Entity::Id idA, idB;
				std::tie(idA, idB) = tuple;


				// emitir evento -> Projectil vs Insect

				// El insecto esta registrado a ese evento

				// Como insecto este es su on_hit() / on_dead()

				events.emit<plague::ProjectilInsectCollisionEvent>(idA, idB);

                auto insect = es.get(idB);

				if (!insect.has_component<plague::StammableComponent>())
				{
					insect.assign<plague::StammableComponent>();
					insect.component<plague::SpiderBrainComponent>().remove();

					// para su comportamiento (IA?)
					auto sprite = insect.component<plague::Sprite2DComponent>().get();
					sprite->get()->setFlippedY(true);

					// su fisica se convierte en dinamica
					auto physics_box_component = insect.component<plague::PhysicsComponent>().get();
					physics_box_component->update_collision_bitmask(DYNAMIC);

					// evento de enemigo muerto
					events.emit<plague::InsectDeadEvent>();
				}
			}
			_destroy.clear();
		}
	}

protected:
	cocos2d::Scene* _scene;
	cocos2d::EventListenerPhysicsContact* _listener;
	std::vector<std::tuple<entityx::Entity::Id, entityx::Entity::Id> > _destroy;
};

}

#endif
