// Component class NavMeshAgentComponent
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _NavMeshAgentCompomnent_H_
#define _NavMeshAgentCompomnent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "navmesh/CCNavMesh.h"
#include "engine/Component/Transform.h"
#include "engine/Component/SceneComponent.h"
#include "engine/Component/3d/Sprite3DComponent.h"

namespace plague {

struct NavMeshAgentCompomnent : public entityx::Component<NavMeshAgentCompomnent>
{
	explicit NavMeshAgentCompomnent(const cocos2d::NavMeshAgentParam& param)
		: node(cocos2d::NavMeshAgent::create(param))
		, configured(false)
	{
		node->retain();
	}

	~NavMeshAgentCompomnent()
	{
		node->release();
	}

	cocos2d::NavMeshAgent* get() const
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

	cocos2d::NavMeshAgent* node;
	bool configured;
};

}

#endif

