#include "MainMenuScene.h"
//
#include "entityx/entityx.h"
// SCENES
// #include "Level00.h"
#include "engine/scene/Level01.h"

// COMPONENTS
#include "engine/component/SceneComponent.h"
#include "engine/component/Transform.h"
#include "engine/component/ui/ButtonUIComponent.h"
#include "engine/component/ui/LabelWithTTFUIComponent.h"

// SYSTEM
#include "engine/system/CocosGeneratorSystem.h"

#include "ui/CocosGUI.h"
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif
// Spriter-Pro
#include "AnimationNode.h"
// Sonido
#include "audio/include/AudioEngine.h"

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

    // Configure audio
	AudioEngine::pauseAll();
    AudioEngine::preload("sounds/anilla.mp3");
	AudioEngine::play2d("music/Retro_Funk.wav", true);


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	auto spider = ex.entities.create();
	spider.assign<plague::SceneComponent>(this, 5);
	spider.assign<plague::Transform>(Vec2(300, 300), 0.3f);  // position and scale
	spider.assign<plague::SpriterModelComponent>("img/enemy/spider/spider.scml", "Player", "walk");



	float button_x = origin.x + (visibleSize.width / 2);
	float button_y = origin.y + (visibleSize.height / 2) + 120;
	auto button = ex.entities.create();
	button.assign<plague::SceneComponent>(this);
	button.assign<plague::Transform>(cocos2d::Vec2(0, 0), 1.0f);
	button.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(128, 128, 128, 255), "PLAY", 32, 1, cocos2d::Vec2::ZERO, 2.5f);
	auto button_1 = button.assign<plague::ButtonUICompomnent>(
	                                        "img/menu/default.png",
												"img/menu/default_hover.png", 
												"img/menu/default_disabled.png",
												[](cocos2d::ui::Button* button) {
													cocos2d::AudioEngine::play2d("sounds/anilla.mp3");
                                                    button->runAction(
                                                            Sequence::create(
                                                                    EaseElasticOut::create(ScaleTo::create(0.25, 0.2)),
                                                                    Hide::create(),
                                                                    CallFunc::create([]() {
                                                                        Director::getInstance()->replaceScene(cocos2d::TransitionFlipX::create(1, Level01::create()));
                                                                    }),
                                                                    nullptr
                                                            )
                                                    );
												});
    button_1->get()->runAction(EaseElasticOut::create(MoveTo::create(2.25, cocos2d::Vec2(button_x, button_y))));



    float button2_x = origin.x + (visibleSize.width / 2);
    float button2_y = origin.y + (visibleSize.height / 2) + 120 - 240;
    auto button2 = ex.entities.create();
    button2.assign<plague::SceneComponent>(this);
    button2.assign<plague::Transform>(cocos2d::Vec2(0, 0), 1.0f);
    button2.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(128, 128, 128, 255), "OPTIONS", 32, 1, cocos2d::Vec2::ZERO, 2.5f);
    auto button_2 = button2.assign<plague::ButtonUICompomnent>(
            "img/menu/default.png",
            "img/menu/default_hover.png",
            "img/menu/default_disabled.png",
            [](cocos2d::ui::Button* button) {

            });
    button_2->get()->runAction(EaseElasticOut::create(MoveTo::create(2.25, cocos2d::Vec2(button2_x, button2_y))));



	float button3_x = origin.x + (visibleSize.width / 2);
	float button3_y = origin.y + (visibleSize.height / 2) + 120 - 480;
	auto button3 = ex.entities.create();
	button3.assign<plague::SceneComponent>(this);
	button3.assign<plague::Transform>(cocos2d::Vec2(0, 0), 1.0f);
	button3.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(128, 128, 128, 255), "EXIT", 32, 1, cocos2d::Vec2::ZERO, 2.5f);
	auto button_3 = button3.assign<plague::ButtonUICompomnent>(
	                                            "img/menu/default.png",
												"img/menu/default_hover.png", 
												"img/menu/default_disabled.png",
												[](cocos2d::ui::Button* button) {
                                                    AudioEngine::end();
                                                    button->runAction(
                                                        Sequence::create(
                                                                EaseElasticOut::create(ScaleTo::create(0.25, 0.2)),
                                                                Hide::create(),
                                                                CallFunc::create([]() {
                                                                    cocos2d::Director::getInstance()->end();
                                                                    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                                                                        exit(0);
                                                                    #endif
                                                                }),
                                                                nullptr
                                                            )
                                                    );
												});
    button_3->get()->runAction(EaseElasticOut::create(MoveTo::create(2.25, cocos2d::Vec2(button3_x, button3_y))));

	ex.systems.add<plague::CocosGeneratorSystem>();
	ex.systems.configure();

	return true;
}

void MainMenuScene::render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection)
{
	cocos2d::Scene::render(renderer, eyeTransform, eyeProjection);
	ex.systems.update_all(1.0f / 60.0f);
}

}
