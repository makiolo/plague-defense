/* struct InsectInvasionEvent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _InsectInvasionEvent_H_
#define _InsectInvasionEvent_H_

#include <cocos2d.h>

namespace plague {

struct InsectInvasionEvent : public entityx::Event<InsectInvasionEvent>
{
	explicit InsectInvasionEvent()
	{
		
	}

	virtual ~InsectInvasionEvent()
	{

	}
};

}

#endif
