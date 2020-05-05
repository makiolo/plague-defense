#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <cocos2d.h>
#include "SceneComponent.h"

namespace plague {

struct Transform : public entityx::Component<Transform>
{
	explicit Transform(cocos2d::Vec2 position_, float scale_)
		: node(nullptr)
		, position(position_)
		, scale(scale_)
		, configured(false)
	{

	}

	~Transform()
	{
		if(node)
		{
			node->removeFromParent();
			node->setVisible(false);
			node->autorelease();
		}
	}

	cocos2d::Node* get() const
	{
		return node;
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::SceneComponent& scene)
	{
		if(!configured)
		{
			node = cocos2d::Node::create();
			node->retain();
			node->setPosition(position);
			node->setScale(scale);
			scene.get()->addChild(node);
			configured = true;
		}
	}

	bool configured;
	cocos2d::Node* node;
	cocos2d::Vec2 position;
	float scale;
};

}

#endif
