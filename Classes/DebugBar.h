#pragma once
#ifndef _DEBUGBAR_H_
#define _DEBUGBAR_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Sprite.h"
#include "Transform.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "MouseMoveCommand.h"

namespace plague {

	struct DebugBar : public entityx::System<DebugBar>, public entityx::Receiver<DebugBar>
	{
		explicit DebugBar(cocos2d::Scene* scene)
			: _scene(scene)
		{
			_label = cocos2d::Label::createWithTTF("Hello world", "fonts/Marker Felt.ttf", 24);
			if (_label == nullptr)
			{
				throw std::exception("Error creating DebugBar ...");
			}
			else
			{
				// position the label on the center of the screen
				_label->setPosition(cocos2d::Vec2(200, 20));
				_label->setColor(cocos2d::Color3B(0, 0, 0));
				_label->setAlignment(cocos2d::TextHAlignment::LEFT);

				// add the label as a child to this layer
				_scene->addChild(_label, 2);
			}
		}

		void configure(entityx::EntityManager& entities, entityx::EventManager& events) override {
			events.subscribe<plague::MouseMoveCommand>(*this);
		}

		void receive(const plague::MouseMoveCommand& command) {
			std::stringstream ss;
			ss << "x: " << command.x << ", y: " << command.y << std::endl;
			_label->setString(ss.str());
		}

		void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override {

		};

	protected:
		cocos2d::Scene* _scene;
		cocos2d::Label* _label;
	};

}

#endif
