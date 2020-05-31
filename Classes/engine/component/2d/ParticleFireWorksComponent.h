// Component class ParticleFireworks
//
// Ricardo Marmolejo García 2020
//
// use: 
//
#pragma once
#ifndef _ParticleFireworksCompomnent_H_
#define _ParticleFireworksCompomnent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/Transform.h"
#include "engine/component/SceneComponent.h"
#include "engine/event/EntityWillDestroyEvent.h"

namespace plague {

struct ParticleFireworksCompomnent : public entityx::Component<ParticleFireworksCompomnent>, public entityx::Receiver<EntityWillDestroyEvent>
{
	explicit ParticleFireworksCompomnent(entityx::Entity::Id whoiam_)
		// : node(cocos2d::ParticleFireworks::create())
		// : node(cocos2d::ParticleFire::create())
		// : node(cocos2d::ParticleRain::create())
		//: node(cocos2d::ParticleSnow::create())
		//: node(cocos2d::ParticleMeteor::create())
		//: node(cocos2d::ParticleGalaxy::create())
		// : node(cocos2d::ParticleSmoke::create())
		: node(cocos2d::ParticleSun::create())
		, whoiam(whoiam_)
		, configured(false)
	{
		node->retain();
	}

	~ParticleFireworksCompomnent()
	{
		node->removeFromParent();
		node->release();
	}

	cocos2d::ParticleSystem* get() const
	{
		return node;
	}

	void reset(entityx::EntityManager& es, entityx::EventManager& events)
	{
		events.subscribe<EntityWillDestroyEvent>(*this);

		node->setDuration(cocos2d::ParticleSystem::DURATION_INFINITY);
		node->setGravity(cocos2d::Vec2(0, -1000));
		node->setPosition(cocos2d::Vec2::ZERO);
		node->setScale(1);
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform, plague::SceneComponent& scene)
	{
		if(!configured)
		{
			transform.configure_fw(es, events, scene);
			reset(es, events);
			transform.get()->addChild(node);
			configured = true;
		}
	}

	void receive(const EntityWillDestroyEvent& event)
	{
		if(whoiam == event.whodie)
		{
			node->setDuration(event.remaining_time);
			node->setLife(event.remaining_time);
		}
	}

	cocos2d::ParticleSystem* node;
	entityx::Entity::Id whoiam;
	bool configured;
};

}

#endif
