/* System class DetectFloorImpactSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _DetectFloorImpactSystem_H_
#define _DetectFloorImpactSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "AutoDestroyDescription.h"
#include "Transform.h"
#include "PhysicsBoxComponent.h"
#include "GravityComponent.h"
#include "Level01Constants.h"
#include "ProjectilComponent.h"
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
#endif

namespace plague {

struct DetectFloorImpactSystem : public entityx::System<DetectFloorImpactSystem>
{
	explicit DetectFloorImpactSystem()
	{

	}

	virtual ~DetectFloorImpactSystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events)
	{
#if USE_AUDIO_ENGINE
		using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
		using namespace CocosDenshion;
#endif

#if USE_AUDIO_ENGINE
		AudioEngine::preload("sounds/rock_impact.mp3");
		AudioEngine::preload("sounds/insect_impact.mp3");
#elif USE_SIMPLE_AUDIO_ENGINE
		SimpleAudioEngine::getInstance()->preloadEffect("sounds/rock_impact.mp3");
		SimpleAudioEngine::getInstance()->preloadEffect("sounds/insect_impact.mp3");
#endif
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
#if USE_AUDIO_ENGINE
		using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
		using namespace CocosDenshion;
#endif

		es.each<plague::Transform, plague::PhysicsComponent, plague::GravityComponent>([=](entityx::Entity entity, plague::Transform& transform, plague::PhysicsComponent& physics, plague::GravityComponent& gravity)
		{
			// projectile is dynamic
			auto pos = transform.node->getPosition();
			if (pos.y < level01::floor)
			{
				if (entity.has_component<plague::ProjectilComponent>())
				{
#if USE_AUDIO_ENGINE
					AudioEngine::play2d("sounds/rock_impact.mp3");
#elif USE_SIMPLE_AUDIO_ENGINE
					SimpleAudioEngine::getInstance()->playEffect("sounds/rock_impact.mp3");
#endif
				}
				else
				{
#if USE_AUDIO_ENGINE
					AudioEngine::play2d("sounds/insect_impact.mp3");
#elif USE_SIMPLE_AUDIO_ENGINE
					SimpleAudioEngine::getInstance()->playEffect("sounds/insect_impact.mp3");
#endif
				}
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
