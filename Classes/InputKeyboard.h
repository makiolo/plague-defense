#pragma once
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "RightCommand.h"
#include "LeftCommand.h"
#include "MouseMoveCommand.h"
#include "utils.h"

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


struct InputKeyboard : public entityx::System<InputKeyboard> {

	explicit InputKeyboard(cocos2d::Scene* scene)
		: _send_right(true)
		, _touched(false)
		, _moved(false)
		, _scene(scene)
		, _spawn_spider(false)
	{
		_listener = cocos2d::EventListenerKeyboard::create();
		_listener->onKeyPressed = CC_CALLBACK_2(InputKeyboard::onKeyPressed, this);
		_listener->onKeyReleased = CC_CALLBACK_2(InputKeyboard::onKeyReleased, this);

		_listener_touch = cocos2d::EventListenerTouchOneByOne::create();
		_listener_touch->onTouchBegan = CC_CALLBACK_2(InputKeyboard::onTouchBegan, this);
		_listener_touch->onTouchMoved = CC_CALLBACK_2(InputKeyboard::onTouchMoved, this);
		_listener_touch->onTouchEnded = CC_CALLBACK_2(InputKeyboard::onTouchEnded, this);

		_listener_mouse = cocos2d::EventListenerMouse::create();
		_listener_mouse->onMouseMove = CC_CALLBACK_1(InputKeyboard::onMouseMove, this);
		_listener_mouse->onMouseUp = CC_CALLBACK_1(InputKeyboard::onMouseUp, this);
		_listener_mouse->onMouseDown = CC_CALLBACK_1(InputKeyboard::onMouseDown, this);
		_listener_mouse->onMouseScroll = CC_CALLBACK_1(InputKeyboard::onMouseScroll, this);

		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, _scene);
		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener_touch, _scene);
		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener_mouse, _scene);
	}

	virtual ~InputKeyboard()
	{
		
	}

	////////////////////////////////////////////////////////////////////////

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		_mapping[keyCode] = true;
	}

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		_mapping[keyCode] = false;
	}

	////////////////////// TOUCH EVENTS /////////////////////////////////////

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

	/////////////////////// 

	void onMouseDown(cocos2d::EventMouse* e)
	{
		_spawn_spider = true;
		_mouse_x = e->getCursorX();
		_mouse_y = e->getCursorY();
	}

	void onMouseUp(cocos2d::EventMouse* e)
	{

	}

	void onMouseMove(cocos2d::EventMouse* e)
	{
		_moved = true;
		_mouse_x = e->getCursorX();
		_mouse_y = e->getCursorY();
	}

	void onMouseScroll(cocos2d::EventMouse* e)
	{

	}

	//////////////////////////////////////////////////////////////////////////////////////////

	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override
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

		if (_spawn_spider)
		{
			plague::SpriteEntity(_scene, entities, "img/enemy/spider.png", cocos2d::Vec2(_mouse_x, _mouse_y), 1.0f);
			_spawn_spider = false;
		}

		if (_moved)
		{
			events.emit<plague::MouseMoveCommand>(_mouse_x, _mouse_y);
			_moved = false;
		}
	};

protected:
	cocos2d::EventListenerKeyboard* _listener;
	cocos2d::EventListenerTouchOneByOne* _listener_touch;
	cocos2d::EventListenerMouse* _listener_mouse;

	bool _send_right;
	DefaultDict<cocos2d::EventKeyboard::KeyCode, bool> _mapping;

	bool _touched;

	bool _moved;
	float _mouse_x;
	float _mouse_y;

	bool _spawn_spider;

	cocos2d::Scene* _scene;
};

}

#endif
