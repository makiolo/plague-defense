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

struct BrainComponent {
	explicit BrainComponent(const std::string& name)
		: root(name)
	{ ; }

	void configure(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform)
	{
		/*
		while(true)
			x = mediana de enemigos
			if(pos.x > x)
				ir a la izquierda (while(no estoy en x))
			else
				ir a la derecha (while(no estoy en x))
			disparar
		*/
		auto seq_01 = root.make_node<myBT::Sequence>();
		seq_01->setAutoReset(true);

			auto selector_01 = seq_01->make_node<myBT::Selector>();
			selector_01->setPriority(true);
			selector_01->setAutoReset(false);

				auto assert_01 = selector_01->make_node<myBT::Assert>();

					auto condition_01 = assert_01->make_node<myBT::Condition>("right?");
					condition_01->setCondition([&](double deltatime) {
						if (x != 0)
						{
							double myposition = transform.node->getPosition().x;
							return myposition < (x - 5);
						}
						return false;
					});

					auto action_01 = assert_01->make_node<myBT::Action>("right");
					action_01->setUpdate([&](double deltatime) {
							events.emit<plague::RightCommand>(true);
							return myBT::RUNNING;
						});
					action_01->setFinish([&](bool interrupted) {
							events.emit<plague::RightCommand>(false);
						});

				auto assert_02 = selector_01->make_node<myBT::Assert>();

					auto condition_02 = assert_02->make_node<myBT::Condition>("left?");
					condition_02->setCondition([&](double deltatime) {
						if (x != 0)
						{
							double myposition = transform.node->getPosition().x;
							return myposition > (x + 5);
						}
						return false;
					});

					auto action_02 = assert_02->make_node<myBT::Action>("left");
					action_02->setUpdate([&](double deltatime) {
							events.emit<plague::LeftCommand>(true);
							return myBT::RUNNING;
						});
					action_02->setFinish([&](bool interrupted) {
							events.emit<plague::LeftCommand>(false);
						});

					auto seq_02 = selector_01->make_node<myBT::Sequence>();

						auto action_03 = seq_02->make_node<myBT::Action>("fire");
						action_03->setUpdate([&](double deltatime) {
							if (x != 0)
							{
								events.emit<plague::FireCommand>();
							}
							return myBT::COMPLETED;
						});

						auto action_04 = seq_02->make_node<myBT::Wait>("wait");
						action_04->setTime(0.08);
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt)
	{
		// procesar sentidos
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

		// events.emit<plague::BrainDebugEvent>();

		// think
		root.update(root.get_name(), dt);
	}

	myBT::Parallel root;
	// sentidos
	double x;  // eje x con mas enemigos
};

}

#endif
