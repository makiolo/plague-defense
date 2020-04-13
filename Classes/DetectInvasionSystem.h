/* System class DetectInvasionSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _DetectInvasionSystem_H_
#define _DetectInvasionSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Transform.h"
#include "InsectComponent.h"
#include "InsectInvasionEvent.h"

namespace plague {

struct DetectInvasionSystem : public entityx::System<DetectInvasionSystem>
{
	explicit DetectInvasionSystem()
	{
		
	}

	virtual ~DetectInvasionSystem()
	{

	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::InsectComponent>([&](entityx::Entity entity, plague::Transform& transform, plague::InsectComponent& insect) {
			auto pos = transform.node->getPosition();
			if(pos.y > 680)
			{
				if (!entity.has_component<plague::AutoDestroyDescription>())
				{
					entity.assign<plague::AutoDestroyDescription>();
					events.emit<plague::InsectInvasionEvent>();
				}
			}
		});	
	}
};

}

#endif
