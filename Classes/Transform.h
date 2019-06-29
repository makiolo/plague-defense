#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <cocos2d.h>

namespace plague {

struct Transform {
	explicit Transform(cocos2d::Node* node_, cocos2d::Vec2 position_initial_, float scale_initial_)
		: node(node_)
		, position_initial(position_initial_)
		, scale_initial(scale_initial_)
	{
		node->retain();
		reset();
	}

	~Transform()
	{
		node->removeFromParent();
		node->release();
	}

	void reset()
	{
		node->setPosition(position_initial);
		node->setScale(scale_initial);
	}

	cocos2d::Node* node;
	cocos2d::Vec2 position_initial;
	float scale_initial;
};

}

#endif
