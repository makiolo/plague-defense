// Component class LayerColor
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _LayerColorCompomnent_H_
#define _LayerColorCompomnent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/Transform.h"
#include "engine/component/SceneComponent.h"

namespace plague {

struct LayerColorCompomnent : public entityx::Component<LayerColorCompomnent>
{
	explicit LayerColorCompomnent(  uint8_t opacity_ = 255,
	                                const cocos2d::Color4B& color = cocos2d::Color4B(185, 220, 234, 255))
		: node(cocos2d::LayerColor::create(color))
		, configured(false)
		, opacity(opacity_)
	{
		node->retain();
	}

	~LayerColorCompomnent()
	{
		node->removeFromParent();
		node->release();
	}

	cocos2d::LayerColor* get() const
	{
		return node;
	}

	void reset()
	{
		node->setPosition(cocos2d::Vec2::ZERO);
		node->setScale(1);
		node->setOpacity(opacity);
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

	cocos2d::LayerColor* node;
	bool configured;
	uint8_t opacity;
};

}

#endif
