#pragma once
#ifndef _BACKBUTTON_H_
#define _BACKBUTTON_H_

#include <cocos2d.h>
#include <random>
#include "MainMenuScene.h"

namespace plague {

struct SpriteEntity {

	explicit SpriteEntity(cocos2d::Scene* scene, entityx::EntityManager& entities, const std::string& resource, cocos2d::Vec2 position, float scale)
	{
		auto building_sprite = cocos2d::Sprite::create(resource);
		if (building_sprite == nullptr)
		{
			throw std::exception("Excepcion loading Sprite()");
		}
		else
		{
			entityx::Entity entity = entities.create();

			// add transform
			auto building_node = cocos2d::Node::create();

			building_node->setPosition(position);
			building_node->setScale(scale);

			scene->addChild(building_node, 2);

			// add sprite
			entity.assign<plague::Sprite>(building_sprite);
			building_node->addChild(building_sprite);
		}
	}

};

struct CloudEntity {
	explicit CloudEntity(cocos2d::Scene* scene, entityx::EntityManager& entities)
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

		for (int i = 0; i < 20; ++i)
		{
			auto cloud = cocos2d::Sprite::create("img/decoration/cloud.png");
			if (cloud == nullptr)
			{
				throw std::exception("Error loading img/decoration/cloud.png");
			}
			else
			{
				entityx::Entity entity = entities.create();

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
			}
		}
	}
};

struct SkyBasic {
	explicit SkyBasic(cocos2d::Scene* scene)
	{
		// cielo
		auto bg = cocos2d::LayerColor::create(cocos2d::Color4B(185, 220, 234, 255));
		scene->addChild(bg, 0);
	}
};

struct ParticleSystem {
	explicit ParticleSystem(cocos2d::Scene* scene)
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
};

struct BackButton {
	explicit BackButton(cocos2d::Scene* scene)
		: _scene(scene)
	{
		auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
		cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

		// add a "close" icon to exit the progress. it's an autorelease object
		auto closeItem = cocos2d::MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(BackButton::menuCloseCallback, this));

		if (closeItem == nullptr ||
			closeItem->getContentSize().width <= 0 ||
			closeItem->getContentSize().height <= 0)
		{
			throw std::exception("Error creating BackButton ...");
		}
		else
		{
			float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
			float y = origin.y + closeItem->getContentSize().height / 2;
			closeItem->setPosition(cocos2d::Vec2(x, y));
		}

		auto menu = cocos2d::Menu::create(closeItem, NULL);
		menu->setPosition(cocos2d::Vec2::ZERO);
		_scene->addChild(menu, 3);
	}

	// Los callbacks deberian estar en la escena
	void menuCloseCallback(cocos2d::Ref* pSender)
	{
		cocos2d::Director::getInstance()->replaceScene(plague::MainMenuScene::create());

		//Close the cocos2d-x game scene and quit the application
		// Director::getInstance()->end();

		/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

		//EventCustom customEndEvent("game_scene_close_event");
		//_eventDispatcher->dispatchEvent(&customEndEvent);
	}

	cocos2d::Scene* _scene;
};

}

#endif