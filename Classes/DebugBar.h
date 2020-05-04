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
#include "LifeLostEvent.h"

namespace plague {

struct DebugBar : public entityx::Component<DebugBar>, public entityx::Receiver<DebugBar>
{
	explicit DebugBar(cocos2d::Scene* scene, entityx::EventManager& events)
		: _scene(scene)
	{
		_label = cocos2d::Label::createWithTTF("Lifes: 0", "fonts/Marker Felt.ttf", 24);
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

		events.subscribe<plague::LifeLostEvent>(*this);
	}

	virtual ~DebugBar()
	{
		_label->removeFromParent();
		_label->setVisible(false);
		_label->autorelease();
	}

	void receive(const plague::LifeLostEvent& command)
	{
		std::stringstream ss;
		ss << "Lifes: " << command.lifes << std::endl;
		_label->setString(ss.str());
	}

protected:
	cocos2d::Scene* _scene;
	cocos2d::Label* _label;
};

}

#endif
