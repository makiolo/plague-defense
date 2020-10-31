/* struct CountDownResetEvent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CountDownReset_H_
#define _CountDownReset_H_

#include <cocos2d.h>

namespace plague {

struct CountDownResetEvent : public entityx::Event<CountDownResetEvent> {
	explicit CountDownResetEvent()
	{
		
	}

	~CountDownResetEvent()
	{

	}
};

}

#endif
