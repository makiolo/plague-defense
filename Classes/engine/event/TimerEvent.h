// struct TimerEvent
//
// Ricardo Marmolejo García 2019
//
// use: 
//
#pragma once
#ifndef _TimerEvent_H_
#define _TimerEvent_H_

#include "entityx/entityx.h"
#include <cocos2d.h>

namespace plague {

struct TimerEvent : public entityx::Event<TimerEvent>
{
	explicit TimerEvent(std::string tag_)
		: tag(std::move(tag_))
	{
		
	}

	~TimerEvent()
    {

    }

	std::string tag;
};

}

#endif
