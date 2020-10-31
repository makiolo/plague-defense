#pragma once
#ifndef _CLOUD_H_
#define _CLOUD_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/Transform.h"
#include "engine/component/SceneComponent.h"

namespace plague {

struct Sprite2DComponent : public entityx::Component<Sprite2DComponent>
{
	explicit Sprite2DComponent( const std::string& appearance_,
	                            uint8_t opacity_ = 255,
	                            cocos2d::Vec2 anchor_point_ = cocos2d::Vec2::ANCHOR_MIDDLE,
	                            const cocos2d::Vec2& offset_position_ = cocos2d::Vec2::ZERO,
	                            float offset_scale_ = 1.0f)
		: sprite(cocos2d::Sprite::create(appearance_))
		, configured(false)
		, opacity(opacity_)
		, anchor_point(anchor_point_)
		, offset_position(offset_position_)
		, offset_scale(offset_scale_)
	{
		sprite->retain();
	}

	~Sprite2DComponent()
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
		sprite->setAnchorPoint(anchor_point);
		sprite->setOpacity(opacity);
		sprite->setPosition(offset_position);
		sprite->setScale(offset_scale);
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
	cocos2d::Vec2 offset_position;
	float offset_scale;
	// configure
	uint8_t opacity;
	cocos2d::Vec2 anchor_point;
};

}

#endif
