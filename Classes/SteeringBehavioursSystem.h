/* System class SteeringBehaviours
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _SteeringBehaviours_H_
#define _SteeringBehaviours_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct SteeringBehavioursSystem : public entityx::System<SteeringBehavioursSystem>
{
	explicit SteeringBehavioursSystem()
	{
		
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		/*
		 * http://www.lagers.org.uk/ai4g/libguides/lg15-force-calc.html
		 *
		 * Alignament (position && direction)
		 * Separation ()
		 * Cohesion
		 * Seek, Flee && Arrive (position && direction)
		 * Pursuit && Evade
		 * Path Following
		 *
		 * Priority weights:
			Wall avoidance
			Obstacle avoidance
			Evade
			Flee
			Flocking
			Separation
			Alignment
			Cohesion
			Seek
			Arrive
			Wander
			Pursuit
			Offset pursuit
			Interpose
			Hide
			Path following
		 */
	}
};

}

#endif
