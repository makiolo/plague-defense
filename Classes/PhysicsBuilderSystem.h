// Es un "Builder System"
// Las PhysicsComponent necesitan en tiempo de construccion:
// - El Sprite
// - Y la descripción de la física
//
// Para solucionar una dependencia en tiempo de construcción:
// Necesito un sistema como este, que reune las dependencias para crear algo
// y se dedica a crear PhysicsComponent
// 
#pragma once
#ifndef _PhysicsBoxSystem_H_
#define _PhysicsBoxSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Transform.h"
#include "Sprite.h"
#include "ProjectilComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsIntrospectionComponent.h"

namespace plague {

struct PhysicsBuilderSystem : public entityx::System<PhysicsBuilderSystem>
{
	explicit PhysicsBuilderSystem()
	{
		
	}

	virtual ~PhysicsBuilderSystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::Sprite, plague::PhysicsDescription, plague::PhysicsIntrospectionComponent>([&](entityx::Entity entity, plague::Transform& transform, plague::Sprite& sprite, plague::PhysicsDescription& physics_desc, plague::PhysicsIntrospectionComponent& introspection)
		{
			auto physics_component = entity.assign<plague::PhysicsComponent>(sprite, physics_desc);

			// crearlo dinamico si es proyectil
			// crearlo estatico si es insecto
			introspection.id = entity.id();

			bool is_projectile = entity.has_component<plague::ProjectilComponent>();
			if (is_projectile)
			{
				introspection.type = "projectil";
				physics_component->update_collision_bitmask(DYNAMIC);
			}
			else  // is enemy
			{
				introspection.type = "insect";
				physics_component->update_collision_bitmask(STATIC);
			}

			// Aplicar fisica al transform
			physics_component->configure_fw(transform, introspection);

			// desacoplamiento del motor de propulsion
			entity.component<plague::PhysicsDescription>().remove();
		});
	}
};

}

#endif
