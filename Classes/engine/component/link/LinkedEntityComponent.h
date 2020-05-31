// Component class LinkedEntity
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _LinkedEntityCompomnent_H_
#define _LinkedEntityCompomnent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/Transform.h"

namespace plague {

struct LinkedEntityCompomnent : public entityx::Component<LinkedEntityCompomnent>
{
	explicit LinkedEntityCompomnent(entityx::Entity::Id child_id_)
		: child_id(child_id_)
		, configured(false)
		, father(nullptr)
		, child(nullptr)
	{
		
	}

	~LinkedEntityCompomnent()
	{
		
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform)
	{
		if(!configured && transform.configured)
		{
			auto child_entity = es.get(child_id);
			auto transform_child = child_entity.component<Transform>().get();
			if(transform_child->configured)
			{
				child = transform_child->get();
				father = transform.get();
				configured = true;
			}
		}

		child->setPosition( father->getPosition() );
		child->setScale( father->getScale() );
	}

	entityx::Entity::Id child_id;
	bool configured;
	//
	cocos2d::Node* father;
	cocos2d::Node* child;
};

}

#endif
