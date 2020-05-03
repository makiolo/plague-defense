/* System class PhysicsAssemblySystem
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

struct PhysicsAssemblySystem : public entityx::System<PhysicsAssemblySystem>
{
	explicit PhysicsAssemblySystem()
	{
		
	}

	virtual ~PhysicsAssemblySystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Sprite, plague::PhysicsDescription, plague::PhysicsIntrospectionComponent>([=](entityx::Entity entity, plague::Sprite& sprite, plague::PhysicsDescription& physics, plague::PhysicsIntrospectionComponent& introspection) {
			entity.component<plague::PhysicsDescription>().remove();
			bool is_projectile = entity.has_component<plague::ProjectilComponent>();
			entity.assign<plague::PhysicsComponent>(entity.id(), sprite, physics, introspection, is_projectile);
		});
	}
};

}

#endif
