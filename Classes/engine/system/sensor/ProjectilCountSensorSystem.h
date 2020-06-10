/*
 * Contar las unidades que existen de tipo "Insecto"
 * y actualizar su ProjectilCountSensorComponent
 */
/* System class ProjectilCountSensorSystem
*
*  Ricardo Marmolejo García 2020
*/
#pragma once
#ifndef _ProjectilCountSensorSystem_H_
#define _ProjectilCountSensorSystem_H_

#include <vector>
#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/Transform.h"
#include "engine/component/type/ProjectilComponent.h"
#include "engine/component/ai/sensor/ProjectilCountSensorComponent.h"

namespace plague {

struct ProjectilCountSensorSystem : public entityx::System<ProjectilCountSensorSystem>
{
	explicit ProjectilCountSensorSystem()
	{
		
	}

	virtual ~ProjectilCountSensorSystem()
	{
		
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		x = 0;
		std::vector<double> positions;
		es.each<plague::ProjectilComponent, plague::Transform>(
				[&](entityx::Entity entity, plague::ProjectilComponent& projectil, plague::Transform& transform) {
					positions.push_back(transform.get()->getPosition().x);
				}
		);
		if (positions.size() > 0)
		{
			std::sort(positions.begin(), positions.end());
			x = positions[positions.size() / 2];
		}
		// Actualizar sensores
		es.each<plague::ProjectilCountSensorComponent>([&](entityx::Entity entity, plague::ProjectilCountSensorComponent& count_sensor) {
			count_sensor.x = x;	
		});
	}

	double x;  // eje x con mas enemigos
};

}

#endif
