// Component class PhysicsNavMeshComponent
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _PhysicsNavMeshCompomnent_H_
#define _PhysicsNavMeshCompomnent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/Component/Transform.h"
#include "engine/Component/SceneComponent.h"

namespace plague {

struct PhysicsNavMeshCompomnent : public entityx::Component<PhysicsNavMeshCompomnent>
{
	explicit PhysicsNavMeshCompomnent(const std::string& filename)
		: node(cocos2d::PhysicsNavMesh::create(filename))
		, configured(false)
	{
		node->retain();
	}

	~PhysicsNavMeshCompomnent()
	{
		node->removeFromParent();
		node->release();
	}

	cocos2d::PhysicsNavMesh* get() const
	{
		return node;
	}

	void reset()
	{
		
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform, plague::SceneComponent& scene)
	{
		if(!configured)
		{
			transform.configure_fw(es, events, scene);
			reset();
			transform.get()->addChild(node);
			configured = true;
		}
	}

	cocos2d::PhysicsNavMesh* node;
	bool configured;
};

}

#endif
