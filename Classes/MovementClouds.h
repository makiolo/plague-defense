#pragma once
#ifndef _MOVEMENTSCLOUDS_H_
#define _MOVEMENTSCLOUDS_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Sprite.h"
#include "Transform.h"
#include "LeftCommand.h"
#include "RightCommand.h"

namespace plague {

struct MovementSystem : public entityx::System<MovementSystem>, public entityx::Receiver<MovementSystem> {

	explicit MovementSystem()
		: _right_command(true)
	{
		;
	}

	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override {
		events.subscribe<plague::LeftCommand>(*this);
		events.subscribe<plague::RightCommand>(*this);
	}

	void receive(const plague::LeftCommand& command) {
		_right_command = false;
	}

	void receive(const plague::RightCommand& command) {
		_right_command = true;
	}

	/*
	Responsabilidad:
		- Leer/Escribir en Transform
	*/
	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override {

		const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	
		es.each<plague::Transform>([=](entityx::Entity entity, plague::Transform& transform) {

			cocos2d::Vec2 position = transform.node->getPosition();
			float scale = transform.node->getScale();
			float bb_width = scale * 100;
			float limit = visibleSize.width + bb_width;

			bool condition;
			if (_right_command)
				condition = (position.x <= limit);
			else
				condition = (position.x > -bb_width);

			if (condition)
			{
				if(_right_command)
					position.x += 1.0f / (8.0f * scale);
				else
					position.x -= 1.0f / (8.0f * scale);
			}
			else
			{
				if (_right_command)
					position.x -= limit;
				else
					position.x += limit;
			}

			// apply new position in transform
			transform.node->setPosition(position);
		});
	};
protected:
	bool _right_command;

};

}

#endif
