/* Component class ProjectilComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _ProjectilComponent_H_
#define _ProjectilComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct ProjectilComponent : public entityx::Component<ProjectilComponent>
{
	explicit ProjectilComponent()
	{
		
	}

	~ProjectilComponent()
    {

    }
};

}

#endif
