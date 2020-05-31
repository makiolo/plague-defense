// Component class NavMeshObstacleComponent
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _NavMeshObstacleCompomnent_H_
#define _NavMeshObstacleCompomnent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "navmesh/CCNavMesh.h"
#include "engine/Component/Transform.h"
#include "engine/Component/SceneComponent.h"
#include "engine/Component/3d/Sprite3DComponent.h"

namespace plague {

struct NavMeshObstacleCompomnent : public entityx::Component<NavMeshObstacleCompomnent>
{
	explicit NavMeshObstacleCompomnent(float radius, float height)
		: node(cocos2d::NavMeshObstacle::create(radius, height))
		, configured(false)
	{
		node->retain();
	}

	~NavMeshObstacleCompomnent()
	{
		node->release();
	}

	cocos2d::NavMeshObstacle* get() const
	{
		return node;
	}

	void reset()
	{
		
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Sprite3DCompomnent& sprite3d)
	{
		if(!configured)
		{
			reset();
            sprite3d.get()->addComponent(node);
			configured = true;
		}
	}

	cocos2d::NavMeshObstacle* node;
	bool configured;
};

}

#endif
