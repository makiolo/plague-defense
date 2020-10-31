/* struct InsectInvasionEvent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _InsectInvasionEvent_H_
#define _InsectInvasionEvent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct InsectInvasionEvent : public entityx::Event<InsectInvasionEvent>
{
	explicit InsectInvasionEvent()
	{
		
	}

	~InsectInvasionEvent()
	{

	}
};

}

#endif
