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
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
#endif
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
#if USE_AUDIO_ENGINE
		using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
		using namespace CocosDenshion;
#endif

#if USE_AUDIO_ENGINE
		AudioEngine::preload("sounds/escape.mp3");
#elif USE_SIMPLE_AUDIO_ENGINE
		SimpleAudioEngine::getInstance()->preloadEffect("sounds/escape.mp3");
#endif
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::InsectComponent>([&](entityx::Entity entity, plague::Transform& transform, plague::InsectComponent& insect) {
			auto pos = transform.get()->getPosition();
			if(pos.y >= level01::ceil)
			{
				if (!entity.has_component<plague::AutoDestroyDescription>())
				{
#if USE_AUDIO_ENGINE
					using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
					using namespace CocosDenshion;
#endif
#if USE_AUDIO_ENGINE
					AudioEngine::play2d("sounds/escape.mp3");
#elif USE_SIMPLE_AUDIO_ENGINE
					SimpleAudioEngine::getInstance()->playEffect("sounds/escape.mp3");
#endif

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
