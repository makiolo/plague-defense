#include "MainMenuScene.h"
//
#include "entityx/entityx.h"
// SCENES
// #include "Level00.h"
#include "Level01.h"
// 
#include "ui/CocosGUI.h"
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif
// Spriter-Pro
#include "AnimationNode.h"
// Sonido
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

namespace plague {

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

#if USE_AUDIO_ENGINE
	AudioEngine::pauseAll();
	AudioEngine::play2d("sounds/negro.mp3");
	AudioEngine::preload("sounds/anilla.mp3");
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/negro.mp3", true);
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/anilla.mp3");
#endif

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//path to your scml in your Resources folder
	auto scml = FileUtils::getInstance()->fullPathForFilename("img/enemy/spider/spider.scml");

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
		spriter->setScale(0.3);
		this->addChild(spriter, 5);
	}

	/////////////////////////////////////////////////////////////


	Vector<MenuItem*> menu_items;

	auto playButton = MenuItemImage::create(
		"img/menu/play.png",
		"img/menu/play_hover.png",
		[&](Ref* sender) {
#if USE_AUDIO_ENGINE
			AudioEngine::play2d("sounds/anilla.mp3");
#elif USE_SIMPLE_AUDIO_ENGINE
			SimpleAudioEngine::getInstance()->playEffect("sounds/anilla.mp3");
#endif
			// Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(2, Level01::create()));
			Director::getInstance()->replaceScene(cocos2d::TransitionFlipX::create(1, Level01::create()));
			// Director::getInstance()->replaceScene(Level01::create());
		});

	float x = origin.x + (visibleSize.width / 2);
	float y = origin.y + (visibleSize.height / 2) + 120;;
	playButton->setPosition(Vec2(x, y));
	menu_items.pushBack(playButton);
	/////////////

	auto exitButton = MenuItemImage::create(
		"img/menu/exit.png",
		"img/menu/exit_hover.png",
		[&](Ref* sender) {
			cocos2d::Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
		});

	float x2 = origin.x + (visibleSize.width / 2);
	float y2 = origin.y + (visibleSize.height / 2) - playButton->getContentSize().height - 40 + 120;
	exitButton->setPosition(Vec2(x2, y2));
	menu_items.pushBack(exitButton);

	/////////////////

	auto button = cocos2d::ui::Button::create("img/menu/default.png", "img/menu/default_hover.png", "img/menu/default_disabled.png");
	// button->setEnabled(false);
	button->setTitleText("TEST");
	button->setTitleFontSize(64);
	// button->setTitleColor(cocos2d::Color3B::BLACK);

	button->getTitleRenderer()->setTextColor(cocos2d::Color4B::GREEN);
	button->getTitleRenderer()->enableShadow(cocos2d::Color4B::BLUE);
	button->getTitleRenderer()->enableOutline(cocos2d::Color4B::RED, 1);
	// button->setScale(10);
	button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
			case ui::Widget::TouchEventType::BEGAN:
				std::cout << "Button 1 press" << std::endl;
				break;
			case ui::Widget::TouchEventType::ENDED:
				std::cout << "Button 1 released" << std::endl;
				break;
			default:
				
				break;
		}
	});
	float x3 = origin.x + (visibleSize.width / 2);
	float y3 = origin.y + (visibleSize.height / 2) - playButton->getContentSize().height - 40 - 200;
	button->setPosition(Vec2(x3, y3));
	this->addChild(button, 1);

	//////////////////////
	/*
	 * writeable text ------> TextField
	 * readonly text -------> Label
	 * campo booleano ------> CheckBox
	 * clamped float -------> Slider
	 * Actions/Lambdas -----> Button
	 *
	 * Other stuff:
	 * Indicar progreso ----> LoadingBar
	 *
	 */
	/////////////////////////////////////////////////////////////////

	auto menu = Menu::createWithArray(menu_items);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

}
