#pragma once
#ifndef _RIGHTCOMMAND_H_
#define _RIGHTCOMMAND_H_

#include <cocos2d.h>

namespace plague {

struct RightCommand {
	explicit RightCommand(bool active_)
		: active(active_)
	{
		
	}

	bool active;
};

}

#endif
