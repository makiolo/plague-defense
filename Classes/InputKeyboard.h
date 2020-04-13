#pragma once
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "RightCommand.h"
#include "LeftCommand.h"
#include "MouseMoveCommand.h"
#include "utils.h"
#include "AutoDestroy.h"
#include "FireCommand.h"
#include "ExitGameCommand.h"
#include "MainMenuScene.h"
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif

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

struct InputSystem : public entityx::System<InputSystem>, cocos2d::Node, public entityx::Receiver<InputSystem> {

	explicit InputSystem(cocos2d::Scene* scene)
		: _send_right(true)
		, _touching(false)
		, _moved(false)
		, _scene(scene)
	{
		_listener = cocos2d::EventListenerKeyboard::create();
		_listener->retain();
		_listener->onKeyPressed = CC_CALLBACK_2(InputSystem::onKeyPressed, this);
		_listener->onKeyReleased = CC_CALLBACK_2(InputSystem::onKeyReleased, this);

		_listener_touch = cocos2d::EventListenerTouchOneByOne::create();
		_listener_touch->retain();
		_listener_touch->onTouchBegan = CC_CALLBACK_2(InputSystem::onTouchBegan, this);
		_listener_touch->onTouchMoved = CC_CALLBACK_2(InputSystem::onTouchMoved, this);
		_listener_touch->onTouchEnded = CC_CALLBACK_2(InputSystem::onTouchEnded, this);

		_listener_mouse = cocos2d::EventListenerMouse::create();
		_listener_mouse->retain();
		_listener_mouse->onMouseMove = CC_CALLBACK_1(InputSystem::onMouseMove, this);
		_listener_mouse->onMouseUp = CC_CALLBACK_1(InputSystem::onMouseUp, this);
		_listener_mouse->onMouseDown = CC_CALLBACK_1(InputSystem::onMouseDown, this);
		_listener_mouse->onMouseScroll = CC_CALLBACK_1(InputSystem::onMouseScroll, this);

		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, _scene);
		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener_touch, _scene);
		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener_mouse, _scene);
	}

	virtual ~InputSystem()
	{
		_scene->getEventDispatcher()->removeEventListener(_listener);
		_scene->getEventDispatcher()->removeEventListener(_listener_touch);
		_scene->getEventDispatcher()->removeEventListener(_listener_mouse);
		
		CC_SAFE_RELEASE_NULL(_listener);
		CC_SAFE_RELEASE_NULL(_listener_touch);
		CC_SAFE_RELEASE_NULL(_listener_mouse);
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override {
		events.subscribe<plague::ExitGameCommand>(*this);
	}

	void receive(const plague::ExitGameCommand& event)
	{
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(2, MainMenuScene::create()));
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

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* e)
	{
		_touching = true;

		// read touch position
		cocos2d::CCPoint touchLocation = touch->getLocationInView();
		touchLocation = cocos2d::CCDirector::sharedDirector()->convertToGL(touchLocation);
		touchLocation = convertToNodeSpace(touchLocation);

		_mouse_x = touchLocation.x;
		_mouse_y = touchLocation.y;

		return true;
	}

	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* e)
	{
		;
	}

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* e)
	{
		_touching = false;
	}

	/////////////////////// 

	void onMouseDown(cocos2d::EventMouse* e)
	{
		_mouse_x = e->getCursorX();
		_mouse_y = e->getCursorY();
	}

	void onMouseUp(cocos2d::EventMouse* e)
	{
		;
	}

	void onMouseMove(cocos2d::EventMouse* e)
	{
		_moved = true;
		_mouse_x = e->getCursorX();
		_mouse_y = e->getCursorY();
	}

	void onMouseScroll(cocos2d::EventMouse* e)
	{
		;
	}

	//////////////////////////////////////////////////////////////////////////////////////////

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		using namespace cocos2d;

#ifdef _WIN32
		if (_mapping[EventKeyboard::KeyCode::KEY_D])
		{
			events.emit<plague::RightCommand>(true);
		}
		else
		{
			events.emit<plague::RightCommand>(false);
		}

		if (_mapping[EventKeyboard::KeyCode::KEY_A])
		{
			events.emit<plague::LeftCommand>(true);
		}
		else
		{
			events.emit<plague::LeftCommand>(false);
		}

		if (_moved)
		{
			events.emit<plague::MouseMoveCommand>(_mouse_x, _mouse_y);
			_moved = false;
		}

		if (_mapping[EventKeyboard::KeyCode::KEY_SPACE])
		{
			events.emit<plague::FireCommand>();
			_mapping[EventKeyboard::KeyCode::KEY_SPACE] = false;
		}

#else
		if (_touching)
		{
			auto quinto = cocos2d::Director::getInstance()->getVisibleSize().width / 5;
			if (_mouse_x > (4*quinto))
			{
				events.emit<plague::RightCommand>(true);
			}
			else if (_mouse_x < quinto)
			{
				events.emit<plague::LeftCommand>(true);
			}
			else
			{
				events.emit<plague::FireCommand>();
				_touching = false;  // avoid autofire
			}
		}
		else
		{
			events.emit<plague::RightCommand>(false);
			events.emit<plague::LeftCommand>(false);
		}
#endif
		if (_mapping[EventKeyboard::KeyCode::KEY_ESCAPE] || _mapping[EventKeyboard::KeyCode::KEY_BACK])
		{
			events.emit<plague::ExitGameCommand>();
			_mapping[EventKeyboard::KeyCode::KEY_ESCAPE] = false;
			_mapping[EventKeyboard::KeyCode::KEY_BACK] = false;
		}
	};

protected:
	cocos2d::EventListenerKeyboard* _listener;
	cocos2d::EventListenerTouchOneByOne* _listener_touch;
	cocos2d::EventListenerMouse* _listener_mouse;

	bool _send_right;
	DefaultDict<cocos2d::EventKeyboard::KeyCode, bool> _mapping;

	bool _touching;

	bool _moved;
	float _mouse_x;
	float _mouse_y;

	cocos2d::Scene* _scene;
};

}

#endif
