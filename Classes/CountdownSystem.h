/* System/Receiver class CountDownSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CountDownSystem_H_
#define _CountDownSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "CountDownReset.h"
#include "StartGame.h"
#include "CountDownCommnad.h"

namespace plague {

struct CountDownSystem : public entityx::System<CountDownSystem>, public entityx::Receiver<CountDownSystem>
{
	explicit CountDownSystem()
		: _countdown_default(3)
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override {
		events.subscribe<plague::CountDownReset>(*this);
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
				events.emit<plague::StartGame>();
				_active = false;
			}
			// debug countdown in DebugBar
			events.emit<plague::CountDownCommand>(_countdown);
		}
	}

	void reset() {
		_active = true;
		_countdown = _countdown_default;
	}

	void receive(const plague::CountDownReset& event) {
		reset();
	}

	float _countdown_default;
	float _countdown;
	bool _active;
};

}

#endif
