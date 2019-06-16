#include "HelloWorldScene.h"
//
#include "SimpleAudioEngine.h"
#include "entityx/entityx.h"

// ENTITY / MODELS
#include "Sprite.h"
#include "Transform.h"
// SYSTEMS
#include "MovementClouds.h"
#include "InputKeyboard.h"
#include "DebugBar.h"
// SCENES
#include "MainMenuScene.h"
// SPAWNERS
#include "utils.h"

USING_NS_CC;

entityx::EntityX ex;

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
    if ( !Scene::init() )
    {
        return false;
    }

	ex.entities.reset();

	entityx::Entity scenary = ex.entities.create();
	scenary.assign<plague::BackButton>(this);
	scenary.assign<plague::SkyBasic>(this);
	scenary.assign<plague::CloudEntity>(this, ex.entities);
	scenary.assign<plague::SpriteEntity>(this, ex.entities, "img/building/level01.png", cocos2d::Vec2(850, 400), 0.8f);

	ex.systems.add<plague::DebugBar>(this);
	ex.systems.add<plague::MovementSystem>();
	ex.systems.add<plague::InputKeyboard>(this);
	ex.systems.configure();

    return true;
}


void Level01::render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection)
{
	cocos2d::Scene::render(renderer, eyeTransform, eyeProjection);
	ex.systems.update<plague::MovementSystem>(0.01f);
	ex.systems.update<plague::InputKeyboard>(0.01f);
}
