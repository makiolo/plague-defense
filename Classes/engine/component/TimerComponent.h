// Component class TimerComponent
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _TimerComponent_H_
#define _TimerComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/event/TimerEvent.h"

namespace plague {

struct TimerComponent : public entityx::Component<TimerComponent>
{
	explicit TimerComponent(const std::string& tag_, double period_secs_, bool once_ = false)
		: tag(tag_)
		, period_secs(period_secs_)
		, once(once_)
		, _internal_clock(0.0)
		, _first(true)
	{
		
	}

	~TimerComponent()
    {

    }

	void update_fw(entityx::EventManager& events, double deltatime)
	{
		_internal_clock += deltatime;
		if(_internal_clock > period_secs)
		{
			if(!once || (once && _first))
			{
				events.emit<plague::TimerEvent>(tag);
			}
			_internal_clock = 0.0;
		}
	}

	std::string tag;
	double period_secs;
	bool once;
	bool _first;
	double _internal_clock;
};

}

#endif
