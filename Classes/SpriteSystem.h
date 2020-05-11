/*
 * Responsable de crear los sprites
 */
/* System class SpriteSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _SpriteSystem_H_
#define _SpriteSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "SceneComponent.h"
#include "Sprite.h"
#include "Transform.h"
#include "ParticleFireWorksComponent.h"
#include "LinkedEntityComponent.h"
#include "LayerColorComponent.h"

namespace plague {

struct SpriteSystem : public entityx::System<SpriteSystem>
{
	explicit SpriteSystem()
	{
		
	}

	virtual ~SpriteSystem()
	{
		
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		es.each<plague::Sprite, plague::Transform, plague::SceneComponent>([&](entityx::Entity entity, plague::Sprite& sprite, plague::Transform& transform, plague::SceneComponent& scene) {
			sprite.configure_fw(es, events, transform, scene);
		});
		es.each<plague::ParticleFireworksCompomnent, plague::Transform, plague::SceneComponent>([&](entityx::Entity entity, plague::ParticleFireworksCompomnent& particle, plague::Transform& transform, plague::SceneComponent& scene) {
			particle.configure_fw(es, events, transform, scene);
		});
		es.each<plague::LinkedEntityCompomnent, plague::Transform>([&](entityx::Entity entity, plague::LinkedEntityCompomnent& linked, plague::Transform& transform) {
			linked.configure_fw(es, events, transform);
		});
		es.each<plague::LayerColorCompomnent, plague::Transform, plague::SceneComponent>([&](entityx::Entity entity, plague::LayerColorCompomnent& layer, plague::Transform& transform, plague::SceneComponent& scene) {
			layer.configure_fw(es, events, transform, scene);
		});
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		configure(es, events);
	}
};

}

#endif
