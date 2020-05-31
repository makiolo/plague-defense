/* Component class StammableComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _StammableComponent_H_
#define _StammableComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct StammableComponent : public entityx::Component<StammableComponent>
{
	explicit StammableComponent()
	{
		
	}
};

}

#endif
