#pragma once
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "ChangeScene.h"
#include "RightCommand.h"
#include "LeftCommand.h"

namespace plague {

template <
	class Key,
	class Value,
	class Comparator = typename std::map<Key, Value>::key_compare,
	class Allocator = typename std::map<Key, Value>::allocator_type
>
class DefaultDict : public std::map<Key, Value, Comparator, Allocator>
{
public:
	Value& at(const Key& key) {
		return std::map<Key, Value, Comparator, Allocator>::operator[](key);
	}
};


struct InputKeyboard : public entityx::System<InputKeyboard>, public entityx::Receiver<InputKeyboard>, public cocos2d::Node
{
	void configure(entityx::EventManager& events)
	{
		events.subscribe<plague::ChangeScene>(*this);

		_listener = cocos2d::EventListenerKeyboard::create();
		_listener->onKeyPressed = CC_CALLBACK_2(InputKeyboard::onKeyPressed, this);
		_listener->onKeyReleased = CC_CALLBACK_2(InputKeyboard::onKeyReleased, this);
	}

	void receive(const plague::ChangeScene& change_scene) {
		change_scene.scene->addChild(this);
		change_scene.scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
	}

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		_mapping[keyCode] = true;
	}

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		_mapping[keyCode] = false;
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		using namespace cocos2d;

		if (_mapping[EventKeyboard::KeyCode::KEY_A] != _mapping[EventKeyboard::KeyCode::KEY_D])
		{
			if (_mapping[EventKeyboard::KeyCode::KEY_D])
			{
				events.emit<plague::RightCommand>();
			}
			else
			{
				events.emit<plague::LeftCommand>();
			}
		}
	};

protected:
	cocos2d::EventListenerKeyboard* _listener;
	DefaultDict<cocos2d::EventKeyboard::KeyCode, bool> _mapping;
};

}

#endif
