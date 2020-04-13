/* System class DetectCollisionSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _DetectCollisionSystem_H_
#define _DetectCollisionSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct DetectCollisionSystem : public entityx::System<DetectCollisionSystem>
{
	explicit DetectCollisionSystem()
	{
		
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		
	}
};

}

#endif
