/* Component class PhysicsIntrospectionComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _IntrospectionComponent_H_
#define _IntrospectionComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct PhysicsIntrospectionComponent : public entityx::Component<PhysicsIntrospectionComponent>
{
	explicit PhysicsIntrospectionComponent()
	{
		
	}

	~PhysicsIntrospectionComponent()
    {

    }

	std::string type;
	entityx::Entity::Id id;
};

}

#endif
