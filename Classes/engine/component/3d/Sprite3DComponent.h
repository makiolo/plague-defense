// Component class Sprite3DComponent
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _Sprite3DCompomnent_H_
#define _Sprite3DCompomnent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/Component/Transform.h"
#include "engine/Component/SceneComponent.h"

namespace plague {

struct Sprite3DCompomnent : public entityx::Component<Sprite3DCompomnent>
{
	explicit Sprite3DCompomnent(const std::string& filename)
		: node(cocos2d::Sprite3D::create(filename))
		, configured(false)
	{
		node->retain();
	}

	~Sprite3DCompomnent()
	{
		node->removeFromParent();
		node->release();
	}

	cocos2d::Sprite3D* get() const
	{
		return node;
	}

	void reset()
	{
        node->setPosition3D(cocos2d::Vec3(0,0,0));
        /*
        node->addComponent(component);
        node->setCameraMask((unsigned short)CameraFlag::USER1);
        */
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

	cocos2d::Sprite3D* node;
	bool configured;
};

}

#endif
