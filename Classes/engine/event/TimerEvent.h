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
	explicit TimerEvent(const std::string& tag_)
		: tag(tag_)
	{
		
	}

	std::string tag;
};

}

#endif
