/* struct CountDownReset
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CountDownReset_H_
#define _CountDownReset_H_

#include <cocos2d.h>

namespace plague {

struct CountDownReset : public entityx::Event<CountDownReset> {
	explicit CountDownReset()
	{
		
	}

	virtual ~CountDownReset()
	{

	}
};

}

#endif
