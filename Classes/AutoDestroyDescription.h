#pragma once
#ifndef _AUTODESTROY_H_
#define _AUTODESTROY_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct AutoDestroyDescription : public entityx::Component<AutoDestroyDescription>
{
	explicit AutoDestroyDescription(float life_ = 0.0f)
		: life(life_)
	{
		;
	}

	float life;
};

}

#endif

