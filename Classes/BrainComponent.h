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
#include "BrainDebugEvent.h"

namespace plague {

class BrainComponent : entityx::Component<BrainComponent>
{
public:
	explicit BrainComponent(entityx::Entity::Id whoami_, const std::string& name)
		: whoami(whoami_)
		, root(name)
		, x(0)
	{ ; }

	~BrainComponent()
	{

	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform)
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
				if (x != 0)
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
				if (x != 0)
				{
					double myposition = transform.node->getPosition().x;
					return myposition > (x + 5);
				}
				return false;
			}
		};
		conditions["right?"] = {
			[&](double deltatime) {
				if (x != 0)
				{
					double myposition = transform.node->getPosition().x;
					return myposition < (x - 5);
				}
				return false;
			}
		};
		conditions["has_enemies?"] = {
			[&](double deltatime) {
				return x != 0;
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

#if 0

#ifdef __unix__
		root.read_ai("/home/ricardomg/dev/plague-defense/example.txt", conditions, actions);
#else
		root.read_ai("e:\\dev\\PlagueDefense\\example.txt", conditions, actions);
#endif

#else

		auto selector_00 = root.make_node<myBT::Selector>("");
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

#ifdef __unix__
		root.write_ai("/home/ricardomg/dev/plague-defense/example.txt", conditions, actions);
#else
		root.write_ai("e:\\dev\\PlagueDefense\\example.txt", conditions, actions);
#endif

#endif
	}

	void update_fw(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
	{
		// procesar sentidos
		// TODO: mover esta lógica concreta a un sistema general
		x = 0;
		std::vector<double> positions;
		es.each<plague::InsectComponent, plague::Transform>(
				[&](entityx::Entity entity, plague::InsectComponent& insect, plague::Transform& transform) {
					positions.push_back(transform.node->getPosition().x);
				}
		);
		if (positions.size() > 0)
		{
			std::sort(positions.begin(), positions.end());
			x = positions[positions.size() / 2];
		}

		// think
		root.update(root.get_name(), dt);
	}

	entityx::Entity::Id whoami;
	myBT::ActionRepository actions;
	myBT::ConditionRepository conditions;
	myBT::Parallel root;
	// sentidos
	double x;  // eje x con mas enemigos
};

}

#endif
