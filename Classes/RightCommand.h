#pragma once
#ifndef _RIGHTCOMMAND_H_
#define _RIGHTCOMMAND_H_

#include <cocos2d.h>

namespace plague {

struct RightCommand {
	explicit RightCommand(entityx::Entity from_, entityx::Entity to_, bool active_)
		: from(from_)
		, to(to_)
		, active(active_)
	{
		
	}

	entityx::Entity from;
	entityx::Entity to;
	bool active;
};

}

#endif
