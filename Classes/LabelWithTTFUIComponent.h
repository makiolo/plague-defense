// Component class LabelWithTTFUIComponent
//
// Ricardo Marmolejo García 2020
//
// use: 
//
// https://docs.cocos2d-x.org/cocos2d-x/v4/en/ui_components/labels.html
// 
#pragma once
#ifndef _LabelWithTTFUICompomnent_H_
#define _LabelWithTTFUICompomnent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Transform.h"
#include "SceneComponent.h"

namespace plague {

struct LabelWithTTFUICompomnent : public entityx::Component<LabelWithTTFUICompomnent >
{
	explicit LabelWithTTFUICompomnent(const cocos2d::Color4B& color_, const std::string& initial_text, float font_size = 18, int offset_zorder_ = 1, const cocos2d::Vec2& offset_ = cocos2d::Vec2::ZERO, float offset_scale_ = 1.0f, const cocos2d::Size& dimensions = cocos2d::Size(500, 100), cocos2d:: TextHAlignment hAlignment_ = cocos2d::TextHAlignment::CENTER, const std::string& font_family = "fonts/SourceCodePro-Black.otf", cocos2d::TextVAlignment vAlignment_ = cocos2d::TextVAlignment::CENTER)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		: node(cocos2d::Label::createWithTTF(initial_text, font_family, font_size, dimensions, hAlignment_, vAlignment_))
#else
		: node(cocos2d::Label::createWithSystemFont(initial_text, font_family, font_size, dimensions, hAlignment_, vAlignment_))
#endif
		, configured(false)
		, color(color_)
		, HAlignment(hAlignment_)
		, Valignment(vAlignment_)
		, offset(offset_)
		, offset_scale(offset_scale_)
		, offset_zorder(offset_zorder_)
	{
		node->retain();
	}

	~LabelWithTTFUICompomnent()
	{
		node->removeFromParent();
		node->release();
	}

	cocos2d::Label* get() const
	{
		return node;
	}

	void reset()
	{
		node->setPosition(offset);
		node->setScale(offset_scale);
		node->setTextColor(color);
		node->setHorizontalAlignment(HAlignment);
		node->setVerticalAlignment(Valignment);
		node->enableShadow();
		node->enableOutline(cocos2d::Color4B::WHITE, 1);
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform, plague::SceneComponent& scene)
	{
		if(!configured)
		{
			transform.configure_fw(es, events, scene);
			reset();
			transform.get()->addChild(node, offset_zorder);
			configured = true;
		}
	}

	cocos2d::Label* node;
	bool configured;
	cocos2d::Vec2 offset;
	float offset_scale;
	int offset_zorder;
	cocos2d::Color4B color;
	cocos2d::TextHAlignment HAlignment;
	cocos2d::TextVAlignment Valignment;
};

}

#endif
