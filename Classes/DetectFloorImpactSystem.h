/* System class DetectFloorImpactSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _DetectFloorImpactSystem_H_
#define _DetectFloorImpactSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "ProjectilComponent.h"
#include "AutoDestroy.h"
#include "Transform.h"

namespace plague {

struct DetectFloorImpactSystem : public entityx::System<DetectFloorImpactSystem>
{
	explicit DetectFloorImpactSystem()
	{
		
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::ProjectilComponent>([=](entityx::Entity entity, plague::Transform& transform, plague::ProjectilComponent& projectil) {
			auto pos = transform.node->getPosition();
			if (pos.y < 214)
			{
				if (!entity.has_component<plague::AutoDestroy>())
				{
					entity.assign<plague::AutoDestroy>();
				}
			}
			});
	}
};

}

#endif
