/* Component class BrainComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _BrainComponent_H_
#define _BrainComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "myBT/myBT.h"
#include "engine/event/character/FireCommand.h"
#include "engine/event/character/LeftCommand.h"
#include "engine/event/character/RightCommand.h"
#include "engine/component/type/InsectComponent.h"
#include "engine/component/2d/Sprite2DComponent.h"
#include "engine/component/Transform.h"
#include "engine/component/ai/sensor/EnemyCountSensorComponent.h"

namespace plague {

class BrainComponent : public entityx::Component<BrainComponent>
{
public:
	explicit BrainComponent(std::string name_)
		: name(std::move(name_))
        , is_configured(false)
	{ ; }

	~BrainComponent()
	{

	}

	void configure_fw(myBT::Parallel* bt, myBT::ConditionRepository& conditions, myBT::ActionRepository& actions, entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform, plague::EnemyCountSensorComponent& count_sensor, plague::CharacterComponent& character)
	{
        context.stack.set<plague::Transform*>("transform", &transform);
        context.stack.set<EnemyCountSensorComponent*>("count_sensor", &count_sensor);
        context.stack.set<CharacterComponent*>("character", &character);

        bt->configure(context, name);
        is_configured = true;
    }

    void update_fw(myBT::Parallel* bt, myBT::ConditionRepository& conditions, myBT::ActionRepository& actions, entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt, plague::Transform& transform, plague::EnemyCountSensorComponent& count_sensor, plague::CharacterComponent& character)
    {
        if (!is_configured)
            configure_fw(bt, conditions, actions, es, events, transform, count_sensor, character);

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
