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
#include "FireCommand.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "InsectComponent.h"
#include "Sprite.h"
#include "Transform.h"
#include "CountSensorComponent.h"

namespace plague {

class BrainComponent : public entityx::Component<BrainComponent>
{
public:
	explicit BrainComponent(entityx::Entity::Id whoami_, const std::string& name)
		: whoami(whoami_)
		, bt(name)
	{ ; }

	~BrainComponent()
	{

	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform, plague::CountSensorComponent& count_sensor)
	{
		// Actions
		actions["left"] = {
			[&]() {
				
			}, [&](double deltatime) {
				events.emit<plague::LeftCommand>(whoami, whoami, true);
				return myBT::RUNNING;
			}, [&](bool interrupted) {
				events.emit<plague::LeftCommand>(whoami, whoami, false);
			} 
		};
		actions["right"] = {
			[&]() {
				
			}, [&](double deltatime) {
				events.emit<plague::RightCommand>(whoami, whoami, true);
				return myBT::RUNNING;
			}, [&](bool interrupted) {
				events.emit<plague::RightCommand>(whoami, whoami, false);
			}
		};
		actions["fire"] = {
			[&]() {

			}, [&](double deltatime) {
				if (count_sensor.x != 0)
				{
					events.emit<plague::FireCommand>(whoami, whoami);
				}
				return myBT::COMPLETED;
			}, [&](bool interrupted) {
				
			}
		};

		// Conditions
		conditions["left?"] = {
			[&](double deltatime) {
				if (count_sensor.x != 0)
				{
					double myposition = transform.get()->getPosition().x;
					return myposition > (count_sensor.x + 5);
				}
				return false;
			}
		};
		conditions["right?"] = {
			[&](double deltatime) {
				if (count_sensor.x != 0)
				{
					double myposition = transform.get()->getPosition().x;
					return myposition < (count_sensor.x - 5);
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

// READ doctor.ai (default behaviour)
#if 0

#ifdef __unix__

#ifdef __ANDROID__
        /*
        // https://discuss.cocos2d-x.org/t/please-help-cocos2d-x-to-determine-whats-the-correct-path-to-save-a-file-on-ios-and-android/5578/19
        Persistant data like savegames, highscores, replays
        Android: Contect.getFilesDir()
        iOS: /Documents (Note it is NOT /Library/Documents)

        Temporary data like user avatars:
        Android: Context.getCacheDir()
        iOS: /Library/Caches
        */
        auto fullpath = cocos2d::FileUtils::getInstance()->getWritablePath() + "/example.json";
        bt.read_ai(fullpath, conditions, actions);
#else
        bt.read_ai("/home/ricardomg/dev/plague-defense/example.txt", conditions, actions);
#endif
#else
		bt.read_ai("e:\\dev\\PlagueDefense\\example.txt", conditions, actions);
#endif

#endif

// WRITE doctor.ai
#if 1
		auto selector_00 = bt.make_node<myBT::Selector>("main_control");
		selector_00->setPriority(true);

			auto assert_00 = selector_00->make_node<myBT::Assert>("");

				auto condition_00 = assert_00->make_node<myBT::Condition>("has_enemies?", conditions.at("has_enemies?"));
				condition_00->setInverse(true);

				auto seq_00 = assert_00->make_node<myBT::Sequence>("");
				seq_00->setAutoReset(true);
					
					auto fortime_000 = seq_00->make_node<myBT::ForTime>("");
					fortime_000->setValueSecs(1.0);
						auto right_00 = fortime_000->make_node<myBT::Action>("right", actions.at("right"));

					auto fortime_001 = seq_00->make_node<myBT::ForTime>("");
					fortime_001->setValueSecs(1.0);
						auto left_00 = fortime_001->make_node<myBT::Action>("left", actions.at("left"));

			auto selector_01 = selector_00->make_node<myBT::Selector>("");
			selector_01->setPriority(true);


				auto assert_01 = selector_01->make_node<myBT::Assert>("");

					auto condition_01 = assert_01->make_node<myBT::Condition>("right?", conditions.at("right?"));
					auto action_01 = assert_01->make_node<myBT::Action>("right", actions.at("right"));

				auto assert_02 = selector_01->make_node<myBT::Assert>("");

					auto condition_02 = assert_02->make_node<myBT::Condition>("left?", conditions.at("left?"));
					auto action_02 = assert_02->make_node<myBT::Action>("left", actions.at("left"));

				auto seq_02 = selector_01->make_node<myBT::Sequence>("");
				seq_02->setAutoReset(true);

					auto action_03 = seq_02->make_node<myBT::Action>("fire", actions.at("fire"));
					auto action_04 = seq_02->make_node<myBT::Wait>("wait");
					action_04->setTime(2.0);

		/*
		 *Arbol nuevo
		 *
		auto selector_00 = bt.make_node<myBT::Selector>("main_control");
		selector_00->setPriority(true);
		selector_00->setAutoReset(true);

			auto sequence_00 = selector_00->make_node<myBT::Sequence>("");
			//sequence_00->setAutoReset(true);

				auto condition_00 = sequence_00->make_node<myBT::Condition>("has_enemies?", conditions.at("has_enemies?"));
				condition_00->setInverse(true);

				auto fortime_000 = sequence_00->make_node<myBT::ForTime>("");
				fortime_000->setValueSecs(1.0);

					auto sequence_01 = fortime_000->make_node<myBT::Sequence>("");
					//sequence_01->setAutoReset(true);

						auto right_00 = sequence_01->make_node<myBT::Action>("right", actions.at("right"));

						auto fortime_001 = sequence_01->make_node<myBT::ForTime>("");
						fortime_001->setValueSecs(1.0);

						auto left_00 = sequence_01->make_node<myBT::Action>("left", actions.at("left"));

			auto selector_01 = selector_00->make_node<myBT::Selector>("");
			selector_01->setPriority(true);

				auto sequence_02 = selector_01->make_node<myBT::Sequence>("");
				//sequence_02->setAutoReset(true);

					auto condition_01 = sequence_02->make_node<myBT::Condition>("right?", conditions.at("right?"));
					auto action_01 = sequence_02->make_node<myBT::Action>("right", actions.at("right"));

				auto sequence_03 = selector_01->make_node<myBT::Sequence>("");
				//sequence_03->setAutoReset(true);

					auto condition_02 = sequence_03->make_node<myBT::Condition>("left?", conditions.at("left?"));
					auto action_02 = sequence_03->make_node<myBT::Action>("left", actions.at("left"));

			auto sequence_04 = selector_00->make_node<myBT::Sequence>("");
			//sequence_04->setAutoReset(true);

				auto action_03 = sequence_04->make_node<myBT::Action>("fire", actions.at("fire"));
				auto action_04 = sequence_04->make_node<myBT::Wait>("wait");
				action_04->setTime(2.0);
		*/


#ifdef __unix__
#ifdef __ANDROID__
        /*
        // https://discuss.cocos2d-x.org/t/please-help-cocos2d-x-to-determine-whats-the-correct-path-to-save-a-file-on-ios-and-android/5578/19
        Persistant data like savegames, highscores, replays
        Android: Contect.getFilesDir()
        iOS: /Documents (Note it is NOT /Library/Documents)

        Temporary data like user avatars:
        Android: Context.getCacheDir()
        iOS: /Library/Caches
        */
        auto fullpath = cocos2d::FileUtils::getInstance()->getWritablePath() + "/example.json";
        bt.write_ai(fullpath, conditions, actions);
#else
        bt.write_ai("/home/ricardomg/dev/plague-defense/example.txt", conditions, actions);
#endif
#else
		bt.write_ai("e:\\dev\\PlagueDefense\\example.txt", conditions, actions);
#endif

#endif
	}

	void update_fw(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt, plague::Transform& transform)
	{
		bt.update(context, bt.get_name(), dt);
	}

	entityx::Entity::Id whoami;
	myBT::ActionRepository actions;
	myBT::ConditionRepository conditions;
	myBT::Parallel bt;
	myBT::Context context;
};

}

#endif
