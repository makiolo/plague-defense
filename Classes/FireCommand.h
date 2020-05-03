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

struct FireCommand {
	explicit FireCommand(entityx::Entity from_, entityx::Entity to_)
		: from(from_)
		, to(to_)

	{
		
	}

	entityx::Entity from;
	entityx::Entity to;
};

}

#endif

