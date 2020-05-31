/* System class DetectFloorImpactSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _DetectFloorImpactSystem_H_
#define _DetectFloorImpactSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/descriptor/AutoDestroyDescription.h"
#include "engine/component/Transform.h"
#include "engine/component/PhysicsComponent.h"
#include "engine/component/StammableComponent.h"
#include "engine/scene/constants/Level01Constants.h"
#include "engine/component/type/ProjectilComponent.h"
#include "audio/include/AudioEngine.h"

namespace plague {

struct DetectFloorImpactSystem : public entityx::System<DetectFloorImpactSystem>
{
	explicit DetectFloorImpactSystem()
	{

	}

	virtual ~DetectFloorImpactSystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		cocos2d::AudioEngine::preload("sounds/rock_impact.mp3");
		cocos2d::AudioEngine::preload("sounds/insect_impact.mp3");
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::PhysicsComponent, plague::StammableComponent>([=](entityx::Entity entity, plague::Transform& transform, plague::PhysicsComponent& physics, plague::StammableComponent& gravity)
		{
			// projectile is dynamic
			auto pos = transform.get()->getPosition();
			if (pos.y < level01::floor)
			{
				if (!entity.has_component<plague::AutoDestroyDescription>())
				{
					if (entity.has_component<plague::ProjectilComponent>())
					{
						cocos2d::AudioEngine::play2d("sounds/rock_impact.mp3");
					}
					else
					{
						cocos2d::AudioEngine::play2d("sounds/insect_impact.mp3");
					}

					//  TODO: retrasar la destrucción, pero hacerlo invisible
					entity.assign<plague::AutoDestroyDescription>(0.5f);
				}
			}
		});
	}
};

}

#endif
