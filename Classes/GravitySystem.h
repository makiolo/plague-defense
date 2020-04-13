/* System class GravitySystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _GravitySystem_H_
#define _GravitySystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "GravityComponent.h"
#include "Transform.h"

namespace plague {

struct GravitySystem : public entityx::System<GravitySystem>
{
	explicit GravitySystem()
	{
		
	}

	virtual ~GravitySystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		/*
		es.each<plague::Transform, plague::GravityComponent>([=](entityx::Entity entity, plague::Transform& transform, plague::GravityComponent& gravity) {
			cocos2d::Vec2 position = transform.node->getPosition();
			gravity.vel += gravity.acc * dt;
			position.y -= gravity.vel * dt;
			transform.node->setPosition(position);
		});
		*/
	}
};

}

#endif
