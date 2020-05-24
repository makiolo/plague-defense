/*
 * Responsable de crear los sprites
 */
/* System class CocosGeneratorSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CocosGeneratorSystem_H_
#define _CocosGeneratorSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "SceneComponent.h"
#include "Sprite.h"
#include "Transform.h"
#include "ParticleFireWorksComponent.h"
#include "LinkedEntityComponent.h"
#include "LayerColorComponent.h"
#include "SpriterModelComponent.h"
#include "LabelWithTTFUIComponent.h"
#include "ButtonUIComponent.h"
#include "LabelWithTTFUIComponent.h"

namespace plague {

struct CocosGeneratorSystem : public entityx::System<CocosGeneratorSystem>
{
	explicit CocosGeneratorSystem()
	{
		
	}

	virtual ~CocosGeneratorSystem()
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
		es.each<plague::SpriterModelComponent, plague::Transform, plague::SceneComponent>([&](entityx::Entity entity, plague::SpriterModelComponent& spriter, plague::Transform& transform, plague::SceneComponent& scene) {
			spriter.configure_fw(es, events, transform, scene);
		});
		es.each<plague::LabelWithTTFUICompomnent, plague::Transform, plague::SceneComponent>([&](entityx::Entity entity, plague::LabelWithTTFUICompomnent& label, plague::Transform& transform, plague::SceneComponent& scene) {
			label.configure_fw(es, events, transform, scene);
		});
		es.each<plague::ButtonUICompomnent, plague::Transform, plague::SceneComponent, plague::LabelWithTTFUICompomnent>([&](entityx::Entity entity, plague::ButtonUICompomnent& button, plague::Transform& transform, plague::SceneComponent& scene, plague::LabelWithTTFUICompomnent& label) {
			button.configure_fw(es, events, transform, scene, label);
		});
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		configure(es, events);
	}
};

}

#endif
