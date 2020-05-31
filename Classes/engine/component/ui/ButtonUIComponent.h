// Component class ButtonUIComponent
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _ButtonUICompomnent_H_
#define _ButtonUICompomnent_H_

#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "entityx/entityx.h"
#include "engine/component/Transform.h"
#include "engine/component/SceneComponent.h"
#include "LabelWithTTFUIComponent.h"

namespace plague {

struct ButtonUICompomnent : public entityx::Component<ButtonUICompomnent>
{
	explicit ButtonUICompomnent(const std::string& normalImage, 
                       			const std::string& selectedImage, 
                       			const std::string& disableImage = "",
								std::function<void(cocos2d::ui::Button*)> press_ = nullptr,
								std::function<void(cocos2d::ui::Button*)> release_ = nullptr)
		: node(cocos2d::ui::Button::create(normalImage, selectedImage, disableImage))
		, configured(false)
		, press(std::move(press_))
		, release(std::move(release_))
	{
		node->retain();
	}

	~ButtonUICompomnent()
	{
		node->removeFromParent();
		node->release();
	}

	cocos2d::ui::Button* get() const
	{
		return node;
	}

	void reset(plague::LabelWithTTFUICompomnent& label)
	{
		node->setPosition(cocos2d::Vec2::ZERO);
		node->setScale(1);
		// primero lo sacamos del transform
		label.get()->removeFromParent();
		node->setTitleLabel(label.get());
		node->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
			switch (type)
			{
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
					if(press)
					{
						press(node);
					}
					break;
				case cocos2d::ui::Widget::TouchEventType::ENDED:
					if(release)
					{
						release(node);
					}
					break;
				default:
					break;
			}
		});
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform, plague::SceneComponent& scene, plague::LabelWithTTFUICompomnent& label)
	{
		if(!configured)
		{
			transform.configure_fw(es, events, scene);
			reset(label);
			transform.get()->addChild(node);
			configured = true;
		}
	}



	// constructor
	cocos2d::ui::Button* node;
	bool configured;
	// behaviour
	std::function<void(cocos2d::ui::Button*)> press;
	std::function<void(cocos2d::ui::Button*)> release;
};

}

#endif
