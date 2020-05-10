/* System/Receiver class BlackboardSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _BlackboardSystem_H_
#define _BlackboardSystem_H_

#include <cocos2d.h>
#include <random>
#include "entityx/entityx.h"
#include "StartGame.h"
#include "CountDownReset.h"
#include "InsectDeadEvent.h"
#include "InsectInvasionEvent.h"
#include "InsectComponent.h"
#include "ProjectilComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsIntrospectionComponent.h"
#include "LifeLostEvent.h"
#include "Level01Constants.h"
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
#endif
#include "SpiderBrainComponent.h"
#include "SceneComponent.h"

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
		events.subscribe<plague::StartGame>(*this);
		events.subscribe<plague::InsectDeadEvent>(*this);
		events.subscribe<plague::InsectInvasionEvent>(*this);

#if USE_AUDIO_ENGINE
		using namespace cocos2d;
#elif USE_SIMPLE_AUDIO_ENGINE
		using namespace CocosDenshion;
#endif

#if USE_AUDIO_ENGINE
		AudioEngine::preload("sounds/Rip.wav");
#elif USE_SIMPLE_AUDIO_ENGINE
		SimpleAudioEngine::getInstance()->preloadEffect("sounds/Rip.wav");
#endif
	}

	void spwan_spider_normal(entityx::EntityManager& es, entityx::EventManager& events, float start_x, float velocity, std::mt19937& gen, std::uniform_int_distribution<> step_dist, std::uniform_real_distribution<> wait_dist, std::normal_distribution<> offset_dist)
	{
		entityx::Entity spider = es.create();
		// Marca la entidad como de tipo Insecto
		spider.assign<plague::InsectComponent>();
		// Fisica
		spider.assign<plague::PhysicsDescription>(false);
		spider.assign<plague::PhysicsIntrospectionComponent>();
		// Comportamiento IA
		spider.assign<plague::SpiderBrainComponent>(spider.id(), "spider");
		// Apariencia
		cocos2d::Scene* scene = cocos2d::Director::getInstance()->getRunningScene();
		spider.assign<plague::SceneComponent>(scene);
		spider.assign<plague::Transform>(plague::level01::enemies, 1.0f);  // position and scale
		spider.assign<plague::Sprite>("img/enemy/spider.png");
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
					for (int stage = 0; stage < 3; ++stage)
					{
						// spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 2)
				{
					for (int stage = 0; stage < 5; ++stage)
					{
						spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column3, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 3)
				{
					for (int stage = 0; stage < 6; ++stage)
					{
						// spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 800.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 4)
				{
					for (int stage = 0; stage < 6; ++stage)
					{
						spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 5)
				{
					for (int stage = 0; stage < 6; ++stage)
					{
						// spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column3, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 330.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column5, 330.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 6)
				{
					for (int stage = 0; stage < 4; ++stage)
					{
						// spwan_spider_normal(es, events, level01::column1, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column2, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column3, 150.0f, gen, step_dist, wait_dist, offset_dist);
						spwan_spider_normal(es, events, level01::column4, 150.0f, gen, step_dist, wait_dist, offset_dist);
						// spwan_spider_normal(es, events, level01::column5, 150.0f, gen, step_dist, wait_dist, offset_dist);
					}
				}
				else if (_level == 7)
				{
					for (int stage = 0; stage < 7; ++stage)
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
					for (int stage = 0; stage < 8; ++stage)
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
					for (int stage = 0; stage < 8; ++stage)
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
					for (int stage = 0; stage < 20; ++stage)
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
					for (int stage = 0; stage < 40; ++stage)
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
					for (int stage = 0; stage < 40; ++stage)
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
					events.emit<plague::CountDownReset>();
					_active = false;
				}
			}
		}
	}

	void receive(const plague::StartGame& event)
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
#if USE_AUDIO_ENGINE
		using namespace cocos2d;
#elif USE_SIMPLE_AUDIO_ENGINE
		using namespace CocosDenshion;
#endif

#if USE_AUDIO_ENGINE
		AudioEngine::play2d("sounds/Rip.wav");
#elif USE_SIMPLE_AUDIO_ENGINE
		SimpleAudioEngine::getInstance()->playEffect("sounds/Rip.wav");
#endif
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

