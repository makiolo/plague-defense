/* struct ExitGameEvent
*
*  Ricardo Marmolejo Garc�a 2019
*/
#pragma once
#ifndef _ExitGameCommand_H_
#define _ExitGameCommand_H_

#include <cocos2d.h>

namespace plague {

struct ExitGameEvent : public entityx::Event<ExitGameEvent>
{
	explicit ExitGameEvent()
	{

	}

	~ExitGameEvent()
    {

    }
};

}

#endif
