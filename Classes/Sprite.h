#pragma once
#ifndef _CLOUD_H_
#define _CLOUD_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Transform.h"

namespace plague {

struct Sprite : public entityx::Component<Sprite>
{
	explicit Sprite(const std::string& appearance_, bool down_ = false, bool left_ = false)
		: sprite(nullptr)
		, appearance(appearance_)
		, down(down_)
		, left(left_)
		, configured(false)
	{
		
	}

	~Sprite()
	{
		if(sprite)
		{
			sprite->removeFromParent();
			sprite->setVisible(false);
			sprite->autorelease();
		}
	}

	cocos2d::Sprite* get() const
	{
		return sprite;
	}


	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform, plague::SceneComponent& scene)
	{
		if(!configured)
		{
			transform.configure_fw(es, events, scene);
			sprite = cocos2d::Sprite::create(appearance);
			sprite->retain();
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
			transform.get()->addChild(sprite);
			configured = true;
		}
	}


	bool configured;
	cocos2d::Sprite* sprite;
	std::string appearance;
	bool down;
	bool left;
};

}

#endif
