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
#include "BlackBoardSystem.h"
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
#include "navmesh/CCNavMesh.h"
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif

USING_NS_CC;

Level01::Level01()
{
	
}
Level01::~Level01()
{
	if (ex)
	{
		ex.reset();
	}
}


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

#ifdef SDKBOX_ENABLED
	sdkbox::PluginAdMob::init();
	sdkbox::PluginAdMob::show("home");
#endif

	ex = std::unique_ptr<entityx::EntityX>(new entityx::EntityX);

	plague::make_clouds(this, ex->entities);
	plague::make_sky(this);



	// auto nav = cocos2d::NavMesh::create("tile.nav", "tile.geo");


	
	auto building = ex->entities.create();
	plague::make_sprite(building, this, "img/building/level01.png", cocos2d::Vec2(850, 400), 0.8f);

	auto scenary = ex->entities.create();
	scenary.assign<plague::DebugBar>(this, ex->events);
	plague::make_back_button(scenary, this, CC_CALLBACK_1(Level01::menuCloseCallback, this));

	auto character = ex->entities.create();
	plague::make_sprite(character, this, "img/character/character.png", cocos2d::Vec2(858, 920), 0.15f);
	character.assign<plague::CharacterComponent>(450.0f);

	// Movimiento de nubes
	ex->systems.add<plague::MovementSystem>();
	// Sistema de entrada (teclado/raton/touch)
	ex->systems.add<plague::InputSystem>(this);
	// Destructor de entidades
	ex->systems.add<plague::AutoDestroySystem>();
	// Cuenta atras del comienzo de la oleada
	ex->systems.add<plague::CountDownSystem>();
	// director de oleadas
	ex->systems.add<plague::BlackboardSystem>();
	// personaje
	ex->systems.add<plague::CharacterSystem>();
	// detección superior (fuera de mapa)
	ex->systems.add<plague::DetectInvasionSystem>();
	// detección inferior (fuera de mapa)
	ex->systems.add<plague::DetectFloorImpactSystem>();
	// sistema físico
	ex->systems.add<plague::PhysicsSystem>(this);
	// generador de física
	ex->systems.add<plague::PhysicsAssemblySystem>();
	// Gravedad simulada
	// ex->systems.add<plague::GravitySystem>();
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
