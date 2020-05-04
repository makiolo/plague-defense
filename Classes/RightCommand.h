#pragma once
#ifndef _RIGHTCOMMAND_H_
#define _RIGHTCOMMAND_H_

#include <cocos2d.h>

namespace plague {

struct RightCommand : public entityx::Event<RightCommand>
{
	explicit RightCommand(entityx::Entity::Id from_, entityx::Entity::Id to_, bool active_)
		: from(from_)
		, to(to_)
		, active(active_)
	{
		
	}

	virtual ~RightCommand()
	{

	}

	entityx::Entity::Id from;
	entityx::Entity::Id to;
	bool active;
};

}

#endif
