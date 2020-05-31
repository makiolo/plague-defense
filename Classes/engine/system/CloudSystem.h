//
// Movimiento de las nubes
//
#pragma once
#ifndef _MOVEMENTSCLOUDS_H_
#define _MOVEMENTSCLOUDS_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/2d/Sprite2DComponent.h"
#include "engine/component/Transform.h"
#include "engine/event/character/LeftCommand.h"
#include "engine/event/character/RightCommand.h"
#include "engine/component/type/CloudComponent.h"

namespace plague {

struct CloudSystem : public entityx::System<CloudSystem> {

	explicit CloudSystem()
		: _right_command(true)
	{
		;
	}

	virtual ~CloudSystem()
	{
		
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override {

		const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	
		es.each<plague::Transform, plague::CloudComponent>([=](entityx::Entity entity, plague::Transform& transform, plague::CloudComponent& cloud) {

			cocos2d::Vec2 position = transform.get()->getPosition();
			float scale = transform.get()->getScale();
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
			transform.get()->setPosition(position);
		});
	};
protected:
	bool _right_command;

};

}

#endif
