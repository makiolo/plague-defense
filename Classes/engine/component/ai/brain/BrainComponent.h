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
	explicit BrainComponent(const std::string& name)
		: bt(name)
        , is_configured(false)
	{ ; }

	~BrainComponent()
	{
		bt.free_childs();
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform, plague::EnemyCountSensorComponent& count_sensor, plague::CharacterComponent& character)
	{
		// Actions
		actions["left"] = {
			[&]() {
			    character.left(true);
			}, [&](double deltatime) {
				return myBT::RUNNING;
			}, [&]() {
				character.left(false);
			}
		};
		actions["right"] = {
			[&]() {
				character.right(true);
			}, [&](double deltatime) {
				return myBT::RUNNING;
			}, [&]() {
				character.right(false);
			}
		};
		actions["fire"] = {
			[&]() {

			}, [&](double deltatime) {
				if (count_sensor.x != 0)
				{
					character.fire(true);
				}
				return myBT::COMPLETED;
			}, [&]() {
				
			}
		};

		// Conditions
		conditions["left?"] = {
			[&](double deltatime) {
				if (count_sensor.x != 0)
				{
					double myposition = transform.get()->getPosition().x;
					return myposition > (count_sensor.x + 10);
				}
				return false;
			}
		};
		conditions["right?"] = {
			[&](double deltatime) {
				if (count_sensor.x != 0)
				{
					double myposition = transform.get()->getPosition().x;
					return myposition < (count_sensor.x - 10);
				}
				return false;
			}
		};
		conditions["has_enemies?"] = {
			[&](double deltatime) {
				return count_sensor.x != 0;
			}
		};

		/*
		while(true)
			if(pos.x > x)
				ir a la izquierda (while(no estoy en x))
			elif(pos.x < x)
				ir a la derecha (while(no estoy en x))
			else
				disparar
		*/

		// Crear 2 bots pasandose el relevo para disparar
		// Prueba de sincronización


		// Para probar la mezcla de comportamiento scriptado con reactivo
		// Si no hay enemigos, patrullar

        auto fullpath = cocos2d::FileUtils::getInstance()->getWritablePath() + "/" + bt.get_name() + ".json";

        if(cocos2d::FileUtils::getInstance()->isFileExist(fullpath)) {

            // READ doctor.ai (default behaviour)
            bt.read_ai(fullpath, conditions, actions);

        }
        else {

            auto name = bt.get_name();

            if(name == "brain2") {

                auto selector_00 = bt.make_node<myBT::Selector>("main_control")->setPriority(true);

                auto assert_00 = selector_00->make_node<myBT::Assert>("assert_00");

                assert_00->make_node<myBT::Condition>("has_enemies?", conditions.at("has_enemies?"))->setInverse(true);

                auto for_00 = assert_00->make_node<myBT::For>("for_00");

                auto seq_00 = for_00->make_node<myBT::Sequence>("seq_00");

                auto fortime_000 = seq_00->make_node<myBT::ForTime>("fortime_000")->setValueMin(0.5)->setValueMax(1.1);

                fortime_000->make_node<myBT::Action>("right", actions.at("right"));

                auto fortime_001 = seq_00->make_node<myBT::ForTime>("fortime_001")->setValueMin(0.5)->setValueMax(1.1);

                fortime_001->make_node<myBT::Action>("left", actions.at("left"));

                auto selector_01 = selector_00->make_node<myBT::Selector>("selector_01")->setPriority(true);

                auto assert_01 = selector_01->make_node<myBT::Assert>("assert_01");

                assert_01->make_node<myBT::Condition>("right?", conditions.at("right?"));
                assert_01->make_node<myBT::Action>("right", actions.at("right"));

                auto assert_02 = selector_01->make_node<myBT::Assert>("assert_02");

                assert_02->make_node<myBT::Condition>("left?", conditions.at("left?"));
                assert_02->make_node<myBT::Action>("left", actions.at("left"));

                auto seq_02 = selector_01->make_node<myBT::Sequence>("seq_02");

                seq_02->make_node<myBT::Action>("fire", actions.at("fire"));

                auto fortime_002 = seq_02->make_node<myBT::ForTime>("fortime_002")->setValueMin(0.2)->setValueMax(0.6);

                fortime_002->make_node<myBT::Running>("mini sleep");
            }
            else
            {
                // unknown IA
                std::abort();
            }

            bt.write_ai(fullpath, conditions, actions);
        }

		bt.configure(context, bt.get_name());

        is_configured = true;
	}

	void update_fw(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt, plague::Transform& transform, plague::EnemyCountSensorComponent& count_sensor, plague::CharacterComponent& character)
	{
        if (!is_configured)
            configure_fw(es, events, transform, count_sensor, character);

        bt.clearTraces(context);
        bt.update(context, bt.get_name(), dt);
        for(auto flow : context)
        {
            std::stringstream ss;
            ss << "\"" << flow.first << "\": " << flow.second.traces.back();
            events.emit<plague::ConsoleInfoEvent>(bt.get_name(), ss.str());
        }
	}

	myBT::ActionRepository actions;
	myBT::ConditionRepository conditions;
	myBT::Parallel bt;
	myBT::Context context;
    bool is_configured;
};

}

#endif
