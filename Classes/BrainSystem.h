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
#include "Sprite.h"
#include "Transform.h"

namespace plague {

struct BrainSystem : public entityx::System<BrainSystem>
{
	explicit BrainSystem()
	{
		
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		myBT::_action_control.clear();

		es.each<plague::BrainComponent, plague::Transform>([&](entityx::Entity entity, plague::BrainComponent& brain, plague::Transform& transform) {
			brain.configure(es, events, transform);
		});
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::BrainComponent>([&](entityx::Entity entity, plague::BrainComponent& brain) {
			brain.update(es, events, dt);
		});
	}
};

}

#endif
