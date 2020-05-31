/* struct LifeLostEvent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _LifeLostEvent_H_
#define _LifeLostEvent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct LifeLostEvent : public entityx::Event<LifeLostEvent>
{
	explicit LifeLostEvent(int lifes_)
		: lifes(lifes_)
	{
		
	}

    virtual ~LifeLostEvent()
    {
        	    
    }

	int lifes;
};

}

#endif
