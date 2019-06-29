/* Component class GravityComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _GravityComponent_H_
#define _GravityComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct GravityComponent {
	explicit GravityComponent(float vel_, float acc_)
		: vel(vel_)
		, acc(acc_)
	{
		
	}

	float acc;
	float vel;
};

}

#endif
