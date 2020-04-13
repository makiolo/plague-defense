/* System class DetectFloorImpactSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _DetectFloorImpactSystem_H_
#define _DetectFloorImpactSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "AutoDestroy.h"
#include "Transform.h"
#include "GravityComponent.h"

namespace plague {

struct DetectFloorImpactSystem : public entityx::System<DetectFloorImpactSystem>
{
	explicit DetectFloorImpactSystem()
	{
		
	}

	virtual ~DetectFloorImpactSystem()
	{

	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::GravityComponent>([=](entityx::Entity entity, plague::Transform& transform, plague::GravityComponent& gravity)
		{
			// projectile is dynamic
			auto pos = transform.node->getPosition();
			if (pos.y < 214)
			{
				if (!entity.has_component<plague::AutoDestroyDescription>())
				{
					entity.assign<plague::AutoDestroyDescription>();
				}
			}
		});
	}
};

}

#endif
