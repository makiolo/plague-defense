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
#include "Level01Constants.h"

namespace plague {

struct DetectInvasionSystem : public entityx::System<DetectInvasionSystem>
{
	explicit DetectInvasionSystem()
	{
		
	}

	virtual ~DetectInvasionSystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/escape.mp3");
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::InsectComponent>([&](entityx::Entity entity, plague::Transform& transform, plague::InsectComponent& insect) {
			auto pos = transform.node->getPosition();
			if(pos.y > level01::ceil)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/escape.mp3");
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
