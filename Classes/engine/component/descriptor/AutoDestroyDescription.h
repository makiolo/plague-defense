#pragma once
#ifndef _AUTODESTROY_H_
#define _AUTODESTROY_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct AutoDestroyDescription : public entityx::Component<AutoDestroyDescription>
{
	explicit AutoDestroyDescription(float life_ = 0.0f, float linked_life_ = 2.0f)
		: life(life_)
		, linked_life(linked_life_)
	{
		;
	}

	~AutoDestroyDescription()
    {

    }

	float life;
	float linked_life;
};

}

#endif

