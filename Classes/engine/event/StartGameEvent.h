/* struct StartGameEvent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _StartGame_H_
#define _StartGame_H_

#include <cocos2d.h>

namespace plague {

struct StartGameEvent : public entityx::Event<StartGameEvent>
{
	explicit StartGameEvent()
	{
		
	}

	~StartGameEvent()
	{

	}
};

}

#endif
