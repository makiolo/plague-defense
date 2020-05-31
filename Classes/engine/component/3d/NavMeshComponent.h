// Component class NavMeshComponent
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _NavMeshCompomnent_H_
#define _NavMeshCompomnent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/Component/Transform.h"
#include "engine/Component/SceneComponent.h"
#include "navmesh/CCNavMesh.h"

namespace plague {

struct NavMeshCompomnent : public entityx::Component<NavMeshCompomnent>
{
	explicit NavMeshCompomnent(const std::string &navFilePath, const std::string &geomFilePath)
		: node(cocos2d::NavMesh::create(navFilePath, geomFilePath))
		, configured(false)
	{
		node->retain();
	}

	~NavMeshCompomnent()
	{
		node->release();
	}

	cocos2d::NavMesh* get() const
	{
		return node;
	}

	void reset()
	{
		
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::SceneComponent& scene)
	{
		if(!configured)
		{
			reset();
            scene.get()->setNavMesh(node);
			configured = true;
		}
	}

	cocos2d::NavMesh* node;
	bool configured;
};

}

#endif
