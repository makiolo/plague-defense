/* System/Receiver class BlackboardSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _BlackboardSystem_H_
#define _BlackboardSystem_H_

#include <cocos2d.h>
#include <random>
#include <engine/component/ai/sensor/ProjectilCountSensorComponent.h>
#include <engine/component/CombatPointsComponent.h>
#include "entityx/entityx.h"
#include "engine/event/StartGameEvent.h"
#include "engine/event/CountDownResetEvent.h"
#include "engine/event/InsectDeadEvent.h"
#include "engine/event/InsectInvasionEvent.h"
#include "engine/component/type/InsectComponent.h"
#include "engine/component/type/ProjectilComponent.h"
#include "engine/component/PhysicsComponent.h"
#include "engine/component/type/PhysicsIntrospectionComponent.h"
#include "engine/event/LifeLostEvent.h"
#include "engine/scene/constants/Level01Constants.h"
#include "audio/include/AudioEngine.h"
#include "engine/component/ai/brain/SpiderBrainComponent.h"
#include "engine/component/SceneComponent.h"
#include "engine/component/2d/ParticleFireWorksComponent.h"
#include "engine/component/link/LinkedEntityComponent.h"

namespace plague {

struct BlackboardSystem : public entityx::System<BlackboardSystem>, public entityx::Receiver<BlackboardSystem>
{
	explicit BlackboardSystem()
		: _active(false)
		, _spawning(false)
		, _insect_total(0)
		, _level(0)
		, _lifes(30)
		, gen(rd())
		, step_dist{ 70, 90 }
		, wait_dist{ 0.2, 0.8 }
		, offset_dist{ 0.0f, 20.0f }
		, _send_lifes(true)
	{
		;
	}

	virtual ~BlackboardSystem()
	{

	}

	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override
	{
		events.subscribe<plague::StartGameEvent>(*this);
		events.subscribe<plague::InsectDeadEvent>(*this);
		events.subscribe<plague::InsectInvasionEvent>(*this);

		cocos2d::AudioEngine::preload("sounds/Rip.wav");
	}

	void spwan_spider_normal(entityx::EntityManager& es, entityx::EventManager& events, float start_x, float velocity, std::mt19937& gen, std::uniform_int_distribution<> step_dist, std::uniform_real_distribution<> wait_dist, std::normal_distribution<> offset_dist)
	{
		cocos2d::Scene* scene = cocos2d::Director::getInstance()->getRunningScene();

		/*
		entityx::Entity fireworks = es.create();
		fireworks.assign<plague::SceneComponent>(scene, 10);
		fireworks.assign<plague::Transform>(cocos2d::Vec2::ZERO, 1.0f);  // position and scale
		fireworks.assign<plague::ParticleFireworksCompomnent>( fireworks.id(), Particle::SUN );

        entityx::Entity health = es.create();
        health.assign<plague::SceneComponent>(scene, 10);
        health.assign<plague::Transform>(cocos2d::Vec2::ZERO, 1.0f);  // position and scale
        health.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(128, 128, 128, 255), "100", 9, 1, cocos2d::Vec2::ZERO, 2.5f);
        */

		entityx::Entity spider = es.create();
		// Vida
		// Ataque
		// Defensa
		// void on_hit()
		// {
		//     me.vida -= (other.ataque - me.defensa);
		// }
		spider.assign<plague::InsectComponent>();
		spider.assign<plague::PhysicsDescription>(false);
		spider.assign<plague::PhysicsIntrospectionComponent>();
		spider.assign<plague::SpiderBrainComponent>("spider");
		spider.assign<plague::SceneComponent>(scene, 3);
		spider.assign<plague::Transform>(plague::level01::enemies, 1.0f);  // position and scale
		spider.assign<plague::Sprite2DComponent>("img/enemy/spider.png");
        spider.assign<plague::ProjectilCountSensorComponent>();
        //
        // spider.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(28, 255, 28, 255), "100", 10, 1, cocos2d::Vec2(0, 80), 2.5f);
        //
        // Componente que indica la vida de la araña
        //
        // spider.assign<plague::LinkedEntityCompomnent>( fireworks.id() );
        // spider.assign<plague::LinkedEntityCompomnent>( health.id() );
        //
        spider.assign<plague::CombatPointsComponent>(100, 1, 0);
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		if(_active)
		{
			_insect_total = 0;
			es.each<plague::Transform, plague::InsectComponent>([&](entityx::Entity entity, plague::Transform & transform, plague::InsectComponent & insect) {
				++_insect_total;
			});

			if (_send_lifes)
			{
				events.emit<plague::LifeLostEvent>(_lifes);
				_send_lifes = false;
			}

			if(_spawning)
			{
				// spawn level
				if(_level == 1)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						// spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						//spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 10.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 2)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						//spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 10.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 3)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 10.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 4)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						//spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 10.0f, gen, step_dist, wait_dist, offset_dist);
						//spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 5)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column3, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 10.0f, gen, step_dist, wait_dist, offset_dist);
						//spwan_spider_normal(es, events, level01::column5, 330.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 6)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 10.0f, gen, step_dist, wait_dist, offset_dist);
						//spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 7)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column3, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 8)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						// spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 800.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 9)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 10)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						spwan_spider_normal(es, events, level01::column1, 250.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 250.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 250.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 330.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column5, 330.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 11)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						spwan_spider_normal(es, events, level01::column1, 250.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 250.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 250.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 330.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column5, 330.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 12)
				{
					for (int stage = 0; stage < 1; ++stage)
					{
						spwan_spider_normal(es, events, level01::column1, 350.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 350.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 350.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 330.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column5, 330.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				_spawning = false;
			}
			else
			{
				if(_insect_total == 0)
				{
					// comprobar que no hay enemigos
					// cuando lleguen a zero
					// avanzamos al siguiente level
					events.emit<plague::CountDownResetEvent>();
					_active = false;
				}
			}
		}
	}

	void receive(const plague::StartGameEvent& event)
	{
		if (!_active)
		{
			_active = true;
			_spawning = true;
			++_level;
		}
	}

	void receive(const plague::InsectDeadEvent& event)
	{
		cocos2d::AudioEngine::play2d("sounds/Rip.wav");
	}

	void receive(const plague::InsectInvasionEvent& event)
	{
		--_lifes;
		_send_lifes = true;
	}

protected:
	bool _active;
	bool _spawning;
	int _level;
	int _lifes;
	int _insect_total;
	bool _send_lifes;
private:
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> step_dist;
	std::uniform_real_distribution<> wait_dist;
	std::normal_distribution<> offset_dist;
};

}

#endif

