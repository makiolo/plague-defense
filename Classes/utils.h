#pragma once
#ifndef _BACKBUTTON_H_
#define _BACKBUTTON_H_

#include <cocos2d.h>
#include <random>
#include <exception>
#include "MainMenuScene.h"
#include "Level01.h"
#include "Cloud.h"
#include "SceneComponent.h"
#include "Transform.h"
#include "Sprite.h"

namespace plague {

void make_clouds(cocos2d::Scene* scene, entityx::EntityManager& entities)
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> total_clouds{ 2, 20 };
	std::uniform_real_distribution<> scale_random{ 0.2, 0.4 };
	std::normal_distribution<> height_random{ 150, 200 };
	std::uniform_int_distribution<> width_random{ 150, 300 };

	int total_random_clouds = total_clouds(gen);
	for (int i = 0; i < total_random_clouds; ++i)
	{
		auto entity = entities.create();

		// aprox
		const int cloud_width = 100;
		const int cloud_height = 40;

		// add transform
		float scale = scale_random(gen);
		cocos2d::Vec2 position((width_random(gen) * (1 + i)) % int(visibleSize.width), height_random(gen));
		position = cocos2d::Vec2(position.x + (scale * cloud_width / 2), visibleSize.height - position.y - scale * (cloud_height / 2));

		entity.assign<plague::SceneComponent>(scene, -1);
		entity.assign<plague::Transform>(position, scale);
		entity.assign<plague::Sprite>("img/decoration/cloud.png");
		entity.assign<plague::CloudComponent>();
	}
}

}

#endif
