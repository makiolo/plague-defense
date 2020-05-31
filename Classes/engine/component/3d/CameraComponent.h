// Component class CameraComponent
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _CameraCompomnent_H_
#define _CameraCompomnent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/Component/SceneComponent.h"

namespace plague {

struct CameraCompomnent : public entityx::Component<CameraCompomnent>
{
	explicit CameraCompomnent()
		: node(cocos2d::Camera::create())
		, configured(false)
	{
		node->retain();
	}

	~CameraCompomnent()
	{
		node->removeFromParent();
		node->release();
	}

	cocos2d::Camera* get() const
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
			scene.get()->addChild(node);
			configured = true;
		}
	}

	cocos2d::Camera* node;
	bool configured;
};

}

#endif
