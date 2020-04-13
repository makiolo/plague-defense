#pragma once
#ifndef _LEFTCOMMAND_H_
#define _LEFTCOMMAND_H_

#include <cocos2d.h>

namespace plague {

struct LeftCommand {
	explicit LeftCommand(bool active_)
		: active(active_)
	{
		
	}

	bool active;
};

}

#endif
