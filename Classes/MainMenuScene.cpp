#include "MainMenuScene.h"
//
#include "entityx/entityx.h"
// SCENES
#include "Level01.h"
#include "ui/CocosGUI.h"
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif
#include <AnimationNode.h>

USING_NS_CC;

namespace plague {

/*
	/*
	if (playButton == nullptr ||
		playButton->getContentSize().width <= 0 ||
		playButton->getContentSize().height <= 0)
	{
		// throw std::exception("Error loading play button.");
	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + visibleSize.height / 2;
		playButton->setPosition(Vec2(x, y));
	}
*/

MainMenuScene::MainMenuScene()
{

}
MainMenuScene::~MainMenuScene()
{
	
}

Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

#ifdef SDKBOX_ENABLED
	// https://developers.google.com/admob/android/interstitial
	sdkbox::PluginAdMob::init();
	sdkbox::PluginAdMob::cache("home");
#endif

#ifdef ENABLE_CLOUD_SAVE
	// https://github.com/sdkbox/sdkbox-sample-sdkboxplay/tree/master/cpp
	// sdkbox::PluginSdkboxPlay::loadAllGameData();
#endif

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//path to your scml in your Resources folder
	auto scml = FileUtils::getInstance()->fullPathForFilename("spriterpro/PlatformerPack/player.scml");

	//AnimationNode is a container which can play multiple animations sourced from a single model.
	auto spriter = Spriter2dX::AnimationNode::create(scml);

	//If the images used in your animation are in a spritesheet you've 
	//loaded into the Cocos2d frame cache, instantiate the AnimationNode like
	//this to load images from there instead:
	// auto spriter = Spriter2dX::AnimationNode::create(scml, Spriter2dX::AnimationNode::cacheLoader());


	//createEntity gives you a SpriterEngine::EntityInstance that you can manipulate.
	//(refer to SpriterPlusPlus API)
	//You can keep an EntityInstance* as long as your AnimationNode instance is
	//retained; it will delete them when it is deleted.
	auto entity = spriter->play("Player");
	if (entity)
	{
		entity->setCurrentAnimation("walk");
		// entity->setTimeRatio(1.0f / 60.0f);
		spriter->setPosition(Vec2(300, 300));
		spriter->setScale(2);
		this->addChild(spriter, 5);
	}

	/////////////////////////////////////////////////////////////


	Vector<MenuItem*> MenuItems;

	auto playButton = MenuItemImage::create(
		"img/menu/play.png",
		"img/menu/play_hover.png",
		[&](Ref* sender) {
			Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(2, Level01::create()));
		});

	float x = origin.x + (visibleSize.width / 2);
	float y = origin.y + (visibleSize.height / 2) + 120;;
	playButton->setPosition(Vec2(x, y));
	MenuItems.pushBack(playButton);
	/////////////

	auto exitButton = MenuItemImage::create(
		"img/menu/exit.png",
		"img/menu/exit_hover.png",
		[&](Ref* sender) {
			cocos2d::Director::getInstance()->end();
		});

	float x2 = origin.x + (visibleSize.width / 2);
	float y2 = origin.y + (visibleSize.height / 2) - playButton->getContentSize().height - 40 + 120;
	exitButton->setPosition(Vec2(x2, y2));
	MenuItems.pushBack(exitButton);
	/////////////////

	auto button = ui::Button::create("img/menu/normal_image.png", "img/menu/disabled_image.png", "img/menu/selected_image.png");
	button->setTitleText("A");
	button->setTitleColor(cocos2d::Color3B::BLACK);
	float x3 = origin.x + (visibleSize.width / 2);
	float y3 = origin.y + (visibleSize.height / 2) - playButton->getContentSize().height - 40 - 200;
	button->setPosition(Vec2(x3, y3));
	this->addChild(button, 1);

	auto menu = Menu::createWithArray(MenuItems);

	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 1);

	return true;
}

}
