// struct ConsoleInfoEvent
//
//
// Created by Ricardo Marmolejo García on 6/3/2020.
//
//
// use: 
//
#pragma once
#ifndef _ConsoleInfoEvent_H_
#define _ConsoleInfoEvent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct ConsoleInfoEvent : public entityx::Event<ConsoleInfoEvent>
{
	explicit ConsoleInfoEvent(std::string from_, std::string message_)
	    : from(std::move(from_))
	    , message(std::move(message_))
	{
		
	}

	std::string from;
	std::string message;
};

}

#endif //_ConsoleInfoEvent_H_