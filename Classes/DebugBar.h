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
#include "CountDownCommnad.h"

namespace plague {

struct DebugBar : public entityx::Receiver<DebugBar>
{
	explicit DebugBar(cocos2d::Scene* scene, entityx::EventManager& events)
		: _scene(scene)
	{
		events.subscribe<plague::MouseMoveCommand>(*this);
		events.subscribe<plague::CountDownCommand>(*this);

		_label = cocos2d::Label::createWithTTF("Hello world", "fonts/Marker Felt.ttf", 24);
		_label->retain();
		if (_label == nullptr)
		{
            // throw std::runtime_exception("Error creating DebugBar ...");
		}
		else
		{
			// position the label on the center of the screen
			_label->setPosition(cocos2d::Vec2(200, 20));
			_label->setColor(cocos2d::Color3B(0, 0, 0));
			_label->setAlignment(cocos2d::TextHAlignment::LEFT);

			// add the label as a child to this layer
			_scene->addChild(_label, 5);
		}
	}

	~DebugBar()
	{
		_label->removeFromParent();
		_label->release();
	}

	void receive(const plague::MouseMoveCommand& command)
	{
		std::stringstream ss;
		ss << "x: " << command.x << ", y: " << command.y << std::endl;
		_label->setString(ss.str());
	}

	void receive(const plague::CountDownCommand& command)
	{
		if (command.countdown > 0.0f)
		{
			std::stringstream ss;
			ss << "countdown: " << command.countdown << std::endl;
			_label->setString(ss.str());
		}
	}

protected:
	cocos2d::Scene* _scene;
	cocos2d::Label* _label;
};

}

#endif
