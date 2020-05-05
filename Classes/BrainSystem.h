/* System class BrainSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _BrainSystem_H_
#define _BrainSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "BrainComponent.h"
#include "SpiderBrainComponent.h"
#include "Sprite.h"
#include "Transform.h"

namespace plague {

struct BrainSystem : public entityx::System<BrainSystem>
{
	explicit BrainSystem()
	{
			
	}

	virtual ~BrainSystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		es.each<plague::BrainComponent, plague::Transform>([&](entityx::Entity entity, plague::BrainComponent& brain, plague::Transform& transform) {
			brain.configure_fw(es, events, transform);
		});
		es.each<plague::SpiderBrainComponent, plague::Transform>([&](entityx::Entity entity, plague::SpiderBrainComponent& brain, plague::Transform& transform) {
			brain.configure_fw(es, events, transform);
		});
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::BrainComponent, plague::Transform>([&](entityx::Entity entity, plague::BrainComponent& brain, plague::Transform& transform) {
			brain.update_fw(es, events, dt, transform);
		});
		es.each<plague::SpiderBrainComponent, plague::Transform>([&](entityx::Entity entity, plague::SpiderBrainComponent& brain, plague::Transform& transform) {
			brain.update_fw(es, events, dt, transform);
		});
	}
};

}

#endif
