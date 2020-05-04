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
#include "AutoDestroyDescription.h"
#include "PhysicsBoxSystem.h"
#include "InsectDeadEvent.h"
#include "ProjectilComponent.h"
#include "GravityComponent.h"

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

		auto bodyA = contact.getShapeA()->getBody();
		auto bodyB = contact.getShapeB()->getBody();

		auto nodeA = bodyA->getNode();
		auto nodeB = bodyB->getNode();

		plague::PhysicsIntrospectionComponent* objA = static_cast<plague::PhysicsIntrospectionComponent*>(nodeA->getUserData());
		plague::PhysicsIntrospectionComponent* objB = static_cast<plague::PhysicsIntrospectionComponent*>(nodeB->getUserData());

		if (objA->type == "projectil" && objB->type == "insect")
		{
			_destroy.push_back(std::make_tuple(objA->id, objB->id));
			return false;
		}
		else if (objB->type == "projectil" && objA->type == "insect")
		{
			_destroy.push_back(std::make_tuple(objB->id, objA->id));
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
		// update physics
		// _scene->getPhysicsWorld()->step(dt);

		bool reupdate = false;

		if (_destroy.size() > 0)
		{
			for (auto& tuple : _destroy)
			{
				entityx::Entity::Id idA, idB;
				std::tie(idA, idB) = tuple;

				auto projectile = es.get(idA);
				auto insect = es.get(idB);

				if (!insect.has_component<plague::GravityComponent>())
				{
					auto transform_component = insect.component<plague::Transform>().get();
					float scaley = transform_component->node->getScaleY();
					if (scaley > 0)
					{
						// se da la vuelta al enemigo
						transform_component->node->setScaleY(scaley * -1);
						// La fisica necesita que la escala de "x" e "y", sean iguales
						float scalex = transform_component->node->getScaleX();
						transform_component->node->setScaleX(scalex * -1);

						// Se le marca como estanpable (TODO: Cambiar nombre de la componente)
						 auto gravity_component = projectile.component<plague::GravityComponent>().get();
						insect.assign<plague::GravityComponent>(gravity_component->vel, gravity_component->acc);

						// para su comportamiento (IA?)
						auto sprite_component = insect.component<plague::Sprite>().get();
						sprite_component->sprite->stopAllActions();

						// su fisica se convierte en dinamica
						auto physics_box_component = insect.component<plague::PhysicsComponent>().get();
						physics_box_component->update_collision_bitmask(DYNAMIC);

						// evento de enemigo muerto
						events.emit<plague::InsectDeadEvent>();
					}
				}
			}
			_destroy.clear();
			reupdate = true;
		}

		if(reupdate)
		{
			// _scene->getPhysicsWorld()->step(dt);
		}
	}

protected:
	cocos2d::Scene* _scene;
	cocos2d::EventListenerPhysicsContact* _listener;
	std::vector<std::tuple<entityx::Entity::Id, entityx::Entity::Id> > _destroy;
};

}

#endif
