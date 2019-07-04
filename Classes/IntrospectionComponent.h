/* Component class IntrospectionComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _IntrospectionComponent_H_
#define _IntrospectionComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct IntrospectionComponent {
	explicit IntrospectionComponent()
	{
		
	}

	entityx::Entity::Id id;
};

}

#endif
