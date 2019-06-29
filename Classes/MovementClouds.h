#pragma once
#ifndef _MOVEMENTSCLOUDS_H_
#define _MOVEMENTSCLOUDS_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Sprite.h"
#include "Transform.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "Cloud.h"

namespace plague {

struct MovementSystem : public entityx::System<MovementSystem> {

	explicit MovementSystem()
		: _right_command(true)
	{
		;
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override {

		const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	
		es.each<plague::Transform, plague::Cloud>([=](entityx::Entity entity, plague::Transform& transform, plague::Cloud& cloud) {

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
					position.x += 1.0f / (60.0f * scale);
				else
					position.x -= 1.0f / (60.0f * scale);
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
