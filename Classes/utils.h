#pragma once
#ifndef _BACKBUTTON_H_
#define _BACKBUTTON_H_

#include <cocos2d.h>
#include <random>
#include <exception>
#include "MainMenuScene.h"
#include "Level01.h"
#include "Cloud.h"

namespace plague {

void make_sprite(entityx::Entity& entity, cocos2d::Scene* scene, const std::string& resource, cocos2d::Vec2 position = cocos2d::Vec2::ZERO, float scale = 1, bool down = false, bool left = false)
{
	auto building_sprite = cocos2d::Sprite::create(resource);
	if (down)
	{
		if (!left)
		{
			building_sprite->setAnchorPoint(cocos2d::Vec2(0.5, 0.0));
		}
		else
		{
			building_sprite->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
		}
	}
	if (building_sprite == nullptr)
	{
#if defined(_HAS_EXCEPTIONS) && defined(__EXCEPTIONS)
		throw std::exception("Excepcion loading Sprite()");
#else
		std::abort();
#endif
	}
	else
	{
		// add transform
		auto building_node = cocos2d::Node::create();
		entity.assign<plague::Transform>(building_node, position, scale);
		scene->addChild(building_node, 2);

		// add sprite
		entity.assign<plague::Sprite>(building_sprite);
		building_node->addChild(building_sprite);
	}
}

void make_clouds(cocos2d::Scene* scene, entityx::EntityManager& entities)
{
	// nubes
	// 
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> scale_random{ 0.2, 0.4 };
	std::normal_distribution<> height_random{ 150, 200 };
	std::uniform_int_distribution<> width_random{ 150, 300 };

	for (int i = 0; i < 10; ++i)
	{
		auto cloud = cocos2d::Sprite::create("img/decoration/cloud.png");
		if (cloud == nullptr)
		{
#if defined(_HAS_EXCEPTIONS) || defined(__EXCEPTIONS)
			// throw std::exception("Error loading img/decoration/cloud.png");
#else
			std::abort();
#endif
		}
		else
		{
			auto entity = entities.create();

			// add transform
			float scale = scale_random(gen);
			cocos2d::Vec2 position((width_random(gen) * (1 + i)) % int(visibleSize.width), height_random(gen));
			position = (cocos2d::Vec2(position.x + (scale * cloud->boundingBox().size.width / 2), visibleSize.height - position.y - scale * (cloud->boundingBox().size.height / 2)));
			auto cloud_node = cocos2d::Node::create();
			scene->addChild(cloud_node, 1);
			entity.assign<plague::Transform>(cloud_node, position, scale);

			// add sprite
			entity.assign<plague::Sprite>(cloud);
			cloud_node->addChild(cloud);

			// add cloud
			entity.assign<plague::CloudComponent>();
		}
	}
}

void make_sky(cocos2d::Scene* scene)
{
	// cielo
	auto bg = cocos2d::LayerColor::create(cocos2d::Color4B(185, 220, 234, 255));
	scene->addChild(bg, 0);
}

void make_particle_system(cocos2d::Scene* scene)
{
	/*
	// probando particulas creadas con: http://particle2dx.com/
	// auto particle_system = ParticleSystem::create("particles/particle_texture.plist");
	auto particle_system = ParticleFireworks::create();
	particle_system->setDuration(ParticleSystem::DURATION_INFINITY);
	if (particle_system == nullptr)
	{
		problemLoading("'particles/particle_texture.plist'");
	}
	else
	{
		// position the sprite on the center of the screen
		particle_system->setPosition(Vec2(150, 100));
		particle_system->setScale(1.2f);

		// add the sprite as a child to this layer
		this->addChild(particle_system, 3);
	}
	*/
}

}

#endif