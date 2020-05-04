#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <cocos2d.h>

namespace plague {

struct Transform : public entityx::Component<Transform>
{
	explicit Transform(cocos2d::Node* node_, cocos2d::Vec2 position_initial_, float scale_initial_)
		: node(node_)
		, position_initial(position_initial_)
		, scale_initial(scale_initial_)
	{
		node->retain();
		node->setPosition(position_initial);
		node->setScale(scale_initial);
	}

	~Transform()
	{
		node->removeFromParent();
		node->setVisible(false);
		node->autorelease();
	}

	/*
	void reset()
	{

	}
	*/

	cocos2d::Node* node;
	cocos2d::Vec2 position_initial;
	float scale_initial;
};

}

#endif
