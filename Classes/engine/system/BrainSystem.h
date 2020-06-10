/* System class BrainSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _BrainSystem_H_
#define _BrainSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/ai/brain/BrainComponent.h"
#include "engine/component/ai/brain/SpiderBrainComponent.h"
#include "engine/component/2d/Sprite2DComponent.h"
#include "engine/component/Transform.h"
#include "engine/component/ai/sensor/EnemyCountSensorComponent.h"
#include "engine/component/ai/sensor/ProjectilCountSensorComponent.h"

namespace plague {

struct BrainSystem : public entityx::System<BrainSystem>
{
	explicit BrainSystem()
	{
			
	}

	virtual ~BrainSystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		es.each<BrainComponent, Transform, EnemyCountSensorComponent, CharacterComponent>([&](entityx::Entity entity, BrainComponent& brain, Transform& transform, EnemyCountSensorComponent& count_sensor, CharacterComponent& character) {
			brain.configure_fw(es, events, transform, count_sensor, character);
		});
		es.each<SpiderBrainComponent, Transform, ProjectilCountSensorComponent>([&](entityx::Entity entity, SpiderBrainComponent& brain, Transform& transform, ProjectilCountSensorComponent& count_sensor) {
			brain.configure_fw(es, events, transform, count_sensor);
		});
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<BrainComponent, Transform, EnemyCountSensorComponent, CharacterComponent>([&](entityx::Entity entity, BrainComponent& brain, Transform& transform, EnemyCountSensorComponent& count_sensor, CharacterComponent& character) {
			brain.update_fw(es, events, dt, transform, count_sensor, character);
		});
		es.each<SpiderBrainComponent, Transform, ProjectilCountSensorComponent>([&](entityx::Entity entity, SpiderBrainComponent& brain, Transform& transform, ProjectilCountSensorComponent& count_sensor) {
			brain.update_fw(es, events, dt, transform, count_sensor);
		});
	}
};

}

#endif
