//
// Cuenta atras del comienzo de la oleada
//
#pragma once
#ifndef _CountDownSystem_H_
#define _CountDownSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/event/CountDownResetEvent.h"
#include "engine/event/StartGameEvent.h"

namespace plague {

struct CountDownSystem : public entityx::System<CountDownSystem>, public entityx::Receiver<CountDownSystem>
{
	explicit CountDownSystem(int countdown_default)
		: _countdown_default(countdown_default)
		, _countdown(0)
		, _active(false)
	{

	}

	virtual ~CountDownSystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override {
		events.subscribe<plague::CountDownResetEvent>(*this);
		// initial reset
		reset();
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override {
		if(_active)
		{
			_countdown -= dt;
			if(_countdown <= 0)
			{
				_countdown = 0;
				events.emit<plague::StartGameEvent>();
				_active = false;
			}
		}
	}

	void reset() {
		_active = true;
		_countdown = _countdown_default;
	}

	void receive(const plague::CountDownResetEvent& event) {
		reset();
	}

	float _countdown_default;
	float _countdown;
	bool _active;
};

}

#endif
