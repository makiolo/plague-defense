#pragma once
#ifndef _CLOUDCOMPONENT_H_
#define _CLOUDCOMPONENT_H_

#include <cocos2d.h>

namespace plague {

struct CloudComponent : entityx::Component<CloudComponent> {
	explicit CloudComponent()
	{
		;
	}

};

}

#endif
