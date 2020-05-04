#pragma once
#ifndef _LEFTCOMMAND_H_
#define _LEFTCOMMAND_H_

#include <cocos2d.h>

namespace plague {

struct LeftCommand : public entityx::Component<LeftCommand>
{
	explicit LeftCommand(entityx::Entity::Id from_, entityx::Entity::Id to_, bool active_)
		: from(from_)
		, to(to_)
		, active(active_)
	{
		
	}

	entityx::Entity::Id from;
	entityx::Entity::Id to;
	bool active;
};

}

#endif
