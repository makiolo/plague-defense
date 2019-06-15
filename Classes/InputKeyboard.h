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
	explicit InputKeyboard()
		: _send_right(true)
		, _touched(false)
	{
		
	}

	void configure(entityx::EventManager& events)
	{
		events.subscribe<plague::ChangeScene>(*this);

		_listener = cocos2d::EventListenerKeyboard::create();
		_listener->onKeyPressed = CC_CALLBACK_2(InputKeyboard::onKeyPressed, this);
		_listener->onKeyReleased = CC_CALLBACK_2(InputKeyboard::onKeyReleased, this);

		_listener_touch = cocos2d::EventListenerTouchOneByOne::create();
		_listener_touch->onTouchBegan = CC_CALLBACK_2(InputKeyboard::onTouchBegan, this);
		_listener_touch->onTouchMoved = CC_CALLBACK_2(InputKeyboard::onTouchMoved, this);
		_listener_touch->onTouchEnded = CC_CALLBACK_2(InputKeyboard::onTouchEnded, this);
	}

	void receive(const plague::ChangeScene& change_scene) {
		change_scene.scene->addChild(this);
		change_scene.scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
		change_scene.scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener_touch, this);
	}

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		_mapping[keyCode] = true;
	}

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		_mapping[keyCode] = false;
	}

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
	{
		_touched = true;
		return true;
	}

	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
	{

	}

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
	{

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

		if (_touched)
		{
			if (_send_right)
			{
				events.emit<plague::RightCommand>();
			}
			else
			{
				events.emit<plague::LeftCommand>();
			}
			_send_right = !_send_right;
			_touched = false;
		}
	};

protected:
	cocos2d::EventListenerKeyboard* _listener;
	cocos2d::EventListenerTouchOneByOne* _listener_touch;
	DefaultDict<cocos2d::EventKeyboard::KeyCode, bool> _mapping;
	bool _send_right;
	bool _touched;
};

}

#endif
