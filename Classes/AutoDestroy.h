#pragma once
#ifndef _AUTODESTROY_H_
#define _AUTODESTROY_H_

#include <cocos2d.h>

namespace plague {

struct AutoDestroy {
	explicit AutoDestroy(float life_ = 0.0f)
		: life(life_)
	{
		;
	}

	float life;
};

}

#endif

