/* Component class FireCommand
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _FireCommand_H_
#define _FireCommand_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct FireCommand : public entityx::Event<FireCommand>
{
	explicit FireCommand(entityx::Entity::Id from_, entityx::Entity::Id to_)
		: from(from_)
		, to(to_)

	{
		
	}

	virtual ~FireCommand()
	{

	}

	entityx::Entity::Id from;
	entityx::Entity::Id to;
};

}

#endif

