/* struct LifeLostEvent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _LifeLostEvent_H_
#define _LifeLostEvent_H_

#include <cocos2d.h>

namespace plague {

struct LifeLostEvent {
	explicit LifeLostEvent(int lifes_)
		: lifes(lifes_)
	{
		
	}

	int lifes;
};

}

#endif
