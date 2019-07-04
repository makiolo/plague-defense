#include "Level01.h"
//
#include "SimpleAudioEngine.h"
#include "entityx/entityx.h"

// COMPONENT
#include "Sprite.h"
#include "Transform.h"
#include "DebugBar.h"
#include "CharacterComponent.h"
// SYSTEMS
#include "MovementClouds.h"
#include "InputKeyboard.h"
#include "AutoDestroySystem.h"
#include "CountdownSystem.h"
#include "BlackboardSystem.h"
#include "DetectInvasionSystem.h"
#include "CharacterSystem.h"
#include "DetectFloorImpactSystem.h"
#include "PhysicsSystem.h"
#include "PhysicsBoxSystem.h"
#include "GravitySystem.h"
// SCENES
#include "MainMenuScene.h"
// SPAWNERS
#include "utils.h"
//

USING_NS_CC;

Scene* Level01::createScene()
{
    return Level01::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Level01::init()
{
    //////////////////////////////
    // 1. super init first
    // if ( !Scene::init() )
	if (!Scene::initWithPhysics())
    {
        return false;
    }

	ex = std::unique_ptr<entityx::EntityX>(new entityx::EntityX);

	plague::make_clouds(this, ex->entities);
	plague::make_sky(this);
	
	auto building = ex->entities.create();
	plague::make_sprite(building, this, "img/building/level01.png", cocos2d::Vec2(850, 400), 0.8f);

	auto scenary = ex->entities.create();
	scenary.assign<plague::DebugBar>(this, ex->events);
	plague::make_back_button(scenary, this, CC_CALLBACK_1(Level01::menuCloseCallback, this));

	auto character = ex->entities.create();
	plague::make_sprite(character, this, "img/character/character.png", cocos2d::Vec2(858, 816), 0.15f);
	character.assign<plague::CharacterComponent>(450.0f);

	ex->systems.add<plague::MovementSystem>();
	ex->systems.add<plague::InputSystem>(this);
	ex->systems.add<plague::AutoDestroySystem>();
	ex->systems.add<plague::CountDownSystem>();
	ex->systems.add<plague::BlackboardSystem>();
	ex->systems.add<plague::DetectInvasionSystem>();
	ex->systems.add<plague::CharacterSystem>();
	ex->systems.add<plague::DetectFloorImpactSystem>();
	ex->systems.add<plague::PhysicsSystem>(this);
	ex->systems.add<plague::PhysicsBoxSystem>();
	ex->systems.add<plague::GravitySystem>();
	ex->systems.configure();

    return true;
}


void Level01::render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection)
{
	cocos2d::Scene::render(renderer, eyeTransform, eyeProjection);
	ex->systems.update_all(1.0f / 60.0f);
}

void Level01::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(2, plague::MainMenuScene::create()));
	// cocos2d::Director::getInstance()->replaceScene(plague::MainMenuScene::create());

	//Close the cocos2d-x game scene and quit the application
	// Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}
