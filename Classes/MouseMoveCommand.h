#pragma once
#ifndef _MOUSEMOVECOMMAND_H_
#define _MOUSEMOVECOMMAND_H_

#include <cocos2d.h>

namespace plague {

struct MouseMoveCommand
{
	explicit MouseMoveCommand(float x_, float y_)
		: x(x_)
		, y(y_)
	{
		;
	}

	float x;
	float y;
};

}

#endif
