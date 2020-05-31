/* Component class PhysicsDescription
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _PhysicsDescription_H_
#define _PhysicsDescription_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct PhysicsDescription : public entityx::Component<PhysicsDescription>
{
	explicit PhysicsDescription(bool dynamic_ = true, cocos2d::Vec2 velocity_ = cocos2d::Vec2::ZERO, float density_ = 1.0f, float restitution_ = 1.0f, float friction_ = 1.0f)
		: dynamic(dynamic_)
		, velocity(velocity_)
		, density(density_)
		, restitution(restitution_)
		, friction(friction_)
	{
		
	}

	/*
	Materials describe material attributes:
		-density: It is used to compute the mass properties of the parent body.
		-restitution: It is used to make objects bounce. The restitution value is usually set to be between 0 and 1. 0 means no bouncing while 1 means perfect bouncing.
		-friction: It is used to make objects slide along each other realistically.
	*/
	bool dynamic;
	cocos2d::Vec2 velocity;
	float density;
	float restitution;
	float friction;
};

}

#endif
