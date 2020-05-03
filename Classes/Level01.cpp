#include "Level01.h"
#include "Level01Constants.h"
//
#include "SimpleAudioEngine.h"
#include "entityx/entityx.h"

// COMPONENT
#include "Sprite.h"
#include "Transform.h"
#include "DebugBar.h"
#include "CharacterComponent.h"
#include "BrainComponent.h"
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
#include "BrainSystem.h"
#include "SteeringBehavioursSystem.h"
// SCENES
#include "MainMenuScene.h"
// SPAWNERS
#include "utils.h"
#include "navmesh/CCNavMesh.h"
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif
// AI
#include "myBT/myBT.h"
// Sounds
// #define USE_AUDIO_ENGINE 1
#define USE_SIMPLE_AUDIO_ENGINE 1
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
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
	// sdkbox::PluginAdMob::show("home");
#endif

	SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/birds.mp3", true);

	ex = std::unique_ptr<entityx::EntityX>(new entityx::EntityX);
	plague::make_clouds(this, ex->entities);
	plague::make_sky(this);
	
	auto building = ex->entities.create();
	plague::make_sprite(building, this, "img/building/newlevel01.png", cocos2d::Vec2::ZERO, 1.0f, true, true);

	auto scenary = ex->entities.create();
	scenary.assign<plague::DebugBar>(this, ex->events);

	auto character = ex->entities.create();
	plague::make_sprite(character, this, "img/character/character.png", plague::level01::player, 0.15f, true);
	character.assign<plague::CharacterComponent>(character, 450.0f);
	// character.assign<plague::BrainComponent>(character, "brain");

	auto character2 = ex->entities.create();
	plague::make_sprite(character2, this, "img/character/character.png", plague::level01::player, 0.30f, true);
	character2.assign<plague::CharacterComponent>(character2, 100.0f);
	character2.assign<plague::BrainComponent>(character2, "brain2");

	/*
	auto character3 = ex->entities.create();
	plague::make_sprite(character3, this, "img/character/character.png", plague::level01::player, 0.21f, true);
	character3.assign<plague::CharacterComponent>(character3, 200.0f);
	character3.assign<plague::BrainComponent>(character3, "brain3");
	*/

	// Movimiento de nubes
	ex->systems.add<plague::MovementSystem>();
	// Sistema de entrada (teclado/raton/touch)
	ex->systems.add<plague::InputSystem>(this, character);
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
	// actualizar IA
	ex->systems.add<plague::BrainSystem>();
	// Steering behaviours system
	ex->systems.add<plague::SteeringBehavioursSystem>();
	ex->systems.configure();

    return true;
}


void Level01::render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection)
{
	cocos2d::Scene::render(renderer, eyeTransform, eyeProjection);
	ex->systems.update_all(1.0f / 60.0f);
}

