// Component class SpriterModelComponent
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _Compomnent_H_
#define _Compomnent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "Transform.h"
#include "SceneComponent.h"
#include "AnimationNode.h"

namespace plague {

struct SpriterModelComponent : public entityx::Component<SpriterModelComponent>
{
	explicit SpriterModelComponent(const std::string& scmlfile, const std::string& entityName_, const std::string& defaultAnimation_)
		: node(Spriter2dX::AnimationNode::create(
					cocos2d::FileUtils::getInstance()->fullPathForFilename(scmlfile)))
		, configured(false)
		, entity(nullptr)
		, entityName(entityName_)
		, defaultAnimation(defaultAnimation_)
	{
		node->retain();
	}

	~SpriterModelComponent()
	{
		if (entity)
		{
			node->deleteEntity(entity);
		}
		node->removeFromParent();
		node->release();
	}

	Spriter2dX::AnimationNode* get() const
	{
		return node;
	}

	void reset()
	{
		entity = node->play(entityName);
		if (entity)
		{
			entity->setCurrentAnimation(defaultAnimation);
			std::cout << entity->getCurrentTime() << std::endl;
		}
		node->setPosition(cocos2d::Vec2::ZERO);
		node->setScale(1);
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

	// Mover a un sistema compartido
	Spriter2dX::AnimationNode* node;
	// Cada modulo spawneado
	SpriterEngine::EntityInstance* entity;
	bool configured;
	std::string entityName;
	std::string defaultAnimation;
};

}

#endif
