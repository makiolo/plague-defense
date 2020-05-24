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
#include "audio/include/AudioEngine.h"
#include "AutoDestroyDescription.h"

namespace plague {

struct DetectInvasionSystem : public entityx::System<DetectInvasionSystem>
{
	explicit DetectInvasionSystem()
	{
		
	}

	virtual ~DetectInvasionSystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		cocos2d::AudioEngine::preload("sounds/escape.mp3");
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::InsectComponent>([&](entityx::Entity entity, plague::Transform& transform, plague::InsectComponent& insect) {
			auto pos = transform.get()->getPosition();
			if(pos.y >= level01::ceil)
			{
				if (!entity.has_component<plague::AutoDestroyDescription>())
				{
					cocos2d::AudioEngine::play2d("sounds/escape.mp3");

					//  TODO: retrasar la destrucción, pero hacerlo invisible
					entity.assign<plague::AutoDestroyDescription>(0.5f);
					events.emit<plague::InsectInvasionEvent>();
				}
			}
		});	
	}
};

}

#endif
