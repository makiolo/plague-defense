#pragma once
#ifndef _MOUSEMOVECOMMAND_H_
#define _MOUSEMOVECOMMAND_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct MouseMoveCommand : public entityx::Event<MouseMoveCommand>
{
	explicit MouseMoveCommand(float x_, float y_)
		: x(x_)
		, y(y_)
	{
		;
	}

	virtual ~MouseMoveCommand()
	{

	}

	float x;
	float y;
};

}

#endif
