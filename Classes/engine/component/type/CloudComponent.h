#pragma once
#ifndef _CLOUDCOMPONENT_H_
#define _CLOUDCOMPONENT_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct CloudComponent : public entityx::Component<CloudComponent> {
	explicit CloudComponent()
	{
		;
	}

	~CloudComponent()
    {

    }

};

}

#endif
