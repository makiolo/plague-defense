/* Component class SpiderBrainComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _SpiderBrainComponent_H_
#define _SpiderBrainComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "myBT/myBT.h"
#include "engine/component/Transform.h"
#include "engine/scene/constants/Level01Constants.h"
#include "engine/event/ConsoleInfoEvent.h"

namespace plague {

struct SpiderBrainComponent : public entityx::Component<SpiderBrainComponent>
{
	explicit SpiderBrainComponent(std::string name_)
		: name(std::move(name_))
		, is_configured(false)
	{
		
	}

	~SpiderBrainComponent()
	{

	}

	void configure_fw(myBT::Parallel* bt, myBT::ConditionRepository& conditions, myBT::ActionRepository& actions, entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform, ProjectilCountSensorComponent& count_sensor)
	{
        context.stack.set<plague::Transform*>("transform", &transform);
        context.stack.set<ProjectilCountSensorComponent*>("count_sensor", &count_sensor);

        bt->configure(context, name);
        is_configured = true;
    }

    void update_fw(myBT::Parallel* bt, myBT::ConditionRepository& conditions, myBT::ActionRepository& actions, entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt, plague::Transform& transform, plague::ProjectilCountSensorComponent& count_sensor)
    {
        if (!is_configured)
            configure_fw(bt, conditions, actions, es, events, transform, count_sensor);

        bt->clearTraces(context);
        bt->update(context, name, dt);
        for(auto flow : context.flows)
        {
            std::stringstream ss;
            ss << "\"" << flow.first << "\": " << flow.second.traces.back();
            events.emit<plague::ConsoleInfoEvent>(name, ss.str());
        }
    }

    std::string name;
    myBT::Context context;
    bool is_configured;
};

}

#endif
