#pragma once
#ifndef _CLOUD_H_
#define _CLOUD_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Transform.h"
#include "SceneComponent.h"

namespace plague {

struct Sprite : public entityx::Component<Sprite>
{
	explicit Sprite(const std::string& appearance_, uint8_t opacity_ = 255, bool down_ = false, bool left_ = false)
		: sprite(cocos2d::Sprite::create(appearance_))
		, configured(false)
		, opacity(opacity_)
		, down(down_)
		, left(left_)
	{
		sprite->retain();
	}

	~Sprite()
	{
		sprite->removeFromParent();
		sprite->release();
	}

	cocos2d::Sprite* get() const
	{
		return sprite;
	}

	void reset()
	{
		if (down)
		{
			if (!left)
			{
				sprite->setAnchorPoint(cocos2d::Vec2(0.5, 0.0));
			}
			else
			{
				sprite->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
			}
		}
		sprite->setOpacity(opacity);
		sprite->setPosition(cocos2d::Vec2::ZERO);
		sprite->setScale(1);
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform, plague::SceneComponent& scene)
	{
		if(!configured)
		{
			transform.configure_fw(es, events, scene);
			reset();
			transform.get()->addChild(sprite);
			configured = true;
		}
	}


	// constructor
	cocos2d::Sprite* sprite;
	bool configured;
	// configure
	uint8_t opacity;
	bool down;
	bool left;
};

}

#endif
