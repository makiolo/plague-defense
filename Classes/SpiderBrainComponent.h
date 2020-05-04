/* Component class SpiderBrainComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _SpiderBrainComponent_H_
#define _SpiderBrainComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct SpiderBrainComponent : public entityx::Component<SpiderBrainComponent>
{
	explicit SpiderBrainComponent(entityx::Entity::Id whoami_, const std::string& name)
		: whoami(whoami_)
		, bt(name)
		, is_configured(false)
	{
		
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform)
	{
		actions["go_to_spawn"] = {
			[&]() {
				const float velocity = 100.0f;
				cocos2d::Vec2 spawn_point = transform.node->getPosition();
				cocos2d::Vec2 start_point(level01::column1, spawn_point.y);
				float start_time = spawn_point.distance(start_point) / velocity;
				transform.node->runAction(cocos2d::MoveBy::create(start_time, start_point - spawn_point));
			}, [&](double deltatime) {
				cocos2d::Vec2 spawn_point = transform.node->getPosition();
				cocos2d::Vec2 start_point(level01::column1, spawn_point.y);
				if(spawn_point.distanceSquared(start_point) > (1.0f*1.0f))
					return myBT::RUNNING;
				else
					return myBT::COMPLETED;
			}, [&](bool interrupted) {
				transform.node->cleanup();
			}
		};

		actions["go_to_roof"] = {
			[&]() {
				const float velocity = 100.0f;
				cocos2d::Vec2 spawn_point = transform.node->getPosition();
				cocos2d::Vec2 start_point(level01::column3, level01::ceil);
				float start_time = spawn_point.distance(start_point) / velocity;
				transform.node->runAction(cocos2d::MoveBy::create(start_time, start_point - spawn_point));
			}, [&](double deltatime) {
				cocos2d::Vec2 spawn_point = transform.node->getPosition();
				cocos2d::Vec2 start_point(level01::column3, level01::ceil);
				if (spawn_point.distanceSquared(start_point) > (1.0f * 1.0f))
					return myBT::RUNNING;
				else
					return myBT::COMPLETED;
			}, [&](bool interrupted) {
				transform.node->cleanup();
			}
		};

		auto sequence_00 = bt.make_node<myBT::Sequence>("main_control");
		sequence_00->make_node<myBT::Action>("go_to_spawn", actions["go_to_spawn"]);
		sequence_00->make_node<myBT::Action>("go_to_roof", actions["go_to_roof"]);

#ifdef __ANDROID__
		/*
        // https://discuss.cocos2d-x.org/t/please-help-cocos2d-x-to-determine-whats-the-correct-path-to-save-a-file-on-ios-and-android/5578/19
        Persistant data like savegames, highscores, replays
        Android: Contect.getFilesDir()
        iOS: /Documents (Note it is NOT /Library/Documents)

        Temporary data like user avatars:
        Android: Context.getCacheDir()
        iOS: /Library/Caches
        */
		auto fullpath = cocos2d::FileUtils::getInstance()->getWritablePath() + "/spider.json";
		bt.write_ai(fullpath, conditions, actions);
#endif
		is_configured = true;
	}

	void update_fw(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt, plague::Transform& transform)
	{
		if (!is_configured)
			configure_fw(es, events, transform);

		bt.update(context, bt.get_name(), dt);
	}

	entityx::Entity::Id whoami;
	myBT::Context context;
	myBT::Parallel bt;
	myBT::ActionRepository actions;
	myBT::ConditionRepository conditions;
	bool is_configured;
};

}

#endif
