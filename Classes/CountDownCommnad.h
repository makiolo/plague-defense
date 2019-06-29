/* struct CountDownCommand
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CountDownCommand_H_
#define _CountDownCommand_H_

#include <cocos2d.h>

namespace plague {

struct CountDownCommand {
	explicit CountDownCommand(float countdown_)
		: countdown(countdown_)
	{
		
	}

	float countdown;
};

}

#endif
