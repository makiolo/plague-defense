/* struct InsectDeadEvent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _InsectDeadEvent_H_
#define _InsectDeadEvent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct InsectDeadEvent : public entityx::Event<InsectDeadEvent>
{
	explicit InsectDeadEvent()
	{
		
	}

	~InsectDeadEvent()
	{

	}
};

}

#endif
