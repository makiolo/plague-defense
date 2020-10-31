/* Component class InsectComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _InsectComponent_H_
#define _InsectComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct InsectComponent : public entityx::Component<InsectComponent>
{
	explicit InsectComponent()
	{
		
	}

    ~InsectComponent()
    {

    }
};

}

#endif
