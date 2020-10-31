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

enum Particle {
    SUN,
    FIREWORKS,
    FIRE,
    RAIN,
    SNOW,
    METEOR,
    GALAXY,
    SMOKE
};

struct ParticleFireworksCompomnent : public entityx::Component<ParticleFireworksCompomnent>, public entityx::Receiver<EntityWillDestroyEvent>
{
	explicit ParticleFireworksCompomnent(entityx::Entity::Id whoiam_, plague::Particle mode = Particle::SUN)
		: whoiam(whoiam_)
		, configured(false)
	{
	    switch(mode)
        {
            case FIREWORKS:
                node = cocos2d::ParticleFireworks::create();
                break;
            case FIRE:
                node = cocos2d::ParticleFire::create();
                break;
            case RAIN:
                node = cocos2d::ParticleRain::create();
                break;
            case SNOW:
                node = cocos2d::ParticleSnow::create();
                break;
            case METEOR:
                node = cocos2d::ParticleMeteor::create();
                break;
            case GALAXY:
                node = cocos2d::ParticleGalaxy::create();
                break;
            case SMOKE:
                node = cocos2d::ParticleSmoke::create();
                break;
            case SUN:
            default:
                node = cocos2d::ParticleSun::create();
                break;
        }
		node->retain();
	}

	virtual ~ParticleFireworksCompomnent()
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
