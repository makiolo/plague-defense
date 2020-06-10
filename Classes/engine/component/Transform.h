#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <cocos2d.h>
#include "engine/component/SceneComponent.h"

namespace plague {

struct Transform : public entityx::Component<Transform>
{
	explicit Transform(cocos2d::Vec2 position_, float scale_)
		: node(cocos2d::Node::create())
		, configured(false)
		, position(position_)
		, scale(scale_)
		, current_action(nullptr)
		, running(false)
	{
		node->retain();
	}

	~Transform()
	{
		node->removeFromParent();
		node->release();
	}

	void runAction(cocos2d::Action* action)
    {
	    if(running) {
            running = false;
            current_action->release();
        }
	    current_action = node->runAction(action);
	    if(!current_action->isDone())
        {
	        running = true;
	        current_action->retain();
        }
    }

    bool isDone() const
    {
	    if(running) {
	        return current_action->isDone();
        }
	    return true;
    }

	cocos2d::Node* get() const
	{
		return node;
	}

	void reset()
	{
		node->setPosition(position);
		node->setScale(scale);
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, SceneComponent& scene)
	{
		if(!configured)
		{			
			reset();
			scene.get()->addChild(node, scene.zorder);
			configured = true;
		}
	}

	cocos2d::Node* node;
	bool configured;
	//
	cocos2d::Vec2 position;
	float scale;
	cocos2d::Action* current_action;
	bool running;
};

}

#endif
