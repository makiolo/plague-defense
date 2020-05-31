// System class TimerSystem
//
// Ricardo Marmolejo García 2019
//
// use: Ejecuta los timers
// Un timer ejectua un evento con cierto periodo
//
#pragma once
#ifndef _TimerSystem_H_
#define _TimerSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/TimerComponent.h"

namespace plague {

struct TimerSystem : public entityx::System<TimerSystem>
{
	explicit TimerSystem()
	{
		
	}

	virtual ~TimerSystem()
	{
		
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<plague::TimerComponent>([&](entityx::Entity entity, plague::TimerComponent& timer) {
			timer.update_fw(events, dt);						
		});
	}
};

}

#endif
