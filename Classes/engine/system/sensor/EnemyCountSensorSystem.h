/*
 * Contar las unidades que existen de tipo "Insecto"
 * y actualizar su EnemyCountSensorComponent
 */
/* System class EnemyCountSensorSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CountSensorSystem_H_
#define _CountSensorSystem_H_

#include <vector>
#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/Transform.h"
#include "engine/component/type/InsectComponent.h"
#include "engine/component/ai/sensor/EnemyCountSensorComponent.h"

namespace plague {

struct EnemyCountSensorSystem : public entityx::System<EnemyCountSensorSystem>
{
	explicit EnemyCountSensorSystem()
	{
		
	}

	virtual ~EnemyCountSensorSystem()
	{
		
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		x = 0;
		std::vector<double> positions;
		es.each<plague::InsectComponent, plague::Transform>(
				[&](entityx::Entity entity, plague::InsectComponent& insect, plague::Transform& transform) {
					positions.push_back(transform.get()->getPosition().x);
				}
		);
		if (positions.size() > 0)
		{
			std::sort(positions.begin(), positions.end());
			x = positions[positions.size() / 2];
		}
		// Actualizar sensores
		es.each<plague::EnemyCountSensorComponent>([&](entityx::Entity entity, plague::EnemyCountSensorComponent& count_sensor) {
			count_sensor.x = x;	
		});
	}

	double x;  // eje x con mas enemigos
};

}

#endif
