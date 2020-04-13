/* Component class CharacterComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CharacterComponent_H_
#define _CharacterComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct CharacterComponent {
	explicit CharacterComponent(float velocity_)
		: velocity(velocity_)
	{
		
	}

	virtual ~CharacterComponent()
	{

	}

	float velocity;
};

}

#endif
