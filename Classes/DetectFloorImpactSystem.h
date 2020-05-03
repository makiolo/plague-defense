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

namespace plague {

struct DetectFloorImpactSystem : public entityx::System<DetectFloorImpactSystem>
{
	explicit DetectFloorImpactSystem()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/escape.mp3");
	}

	virtual ~DetectFloorImpactSystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/rock_impact.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/insect_impact.mp3");
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::Transform, plague::PhysicsComponent, plague::GravityComponent>([=](entityx::Entity entity, plague::Transform& transform, plague::PhysicsComponent& physics, plague::GravityComponent& gravity)
		{
			// projectile is dynamic
			auto pos = transform.node->getPosition();
			if (pos.y < level01::floor)
			{
				if (entity.has_component<plague::ProjectilComponent>())
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/rock_impact.mp3");
				}
				else
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/insect_impact.mp3");
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
