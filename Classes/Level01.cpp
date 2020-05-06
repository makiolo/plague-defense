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
#include "CountSensorComponent.h"
#include "SceneComponent.h"
#include "TimerComponent.h"
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
#include "PhysicsBuilderSystem.h"
#include "BrainSystem.h"
#include "SteeringBehavioursSystem.h"
#include "SpriteSystem.h"
#include "CountSensorSystem.h"
#include "TimerSystem.h"

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
// #define USE_SIMPLE_AUDIO_ENGINE 0
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

}


Scene* Level01::createScene()
{
    return Level01::create();
}

// Print useful error message instead of segfaulting when files are not there.
/*
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
*/

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

#if USE_AUDIO_ENGINE
	AudioEngine::pauseAll();
	AudioEngine::play2d("sounds/birds.mp3");
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/birds.mp3", true);
#endif

	// plague::make_clouds(this, ex.entities);
	// plague::make_sky(this);
	plague::make_particle_system(this);
	
	auto building = ex.entities.create();
	building.assign<plague::SceneComponent>(this);
	building.assign<plague::Transform>(cocos2d::Vec2::ZERO, 1.0f);  // position and scale
	building.assign<plague::Sprite>("img/building/newlevel01.png", true, true);

	auto scenary = ex.entities.create();
	scenary.assign<plague::DebugBar>(this, ex.events);

	auto character = ex.entities.create();
	character.assign<plague::SceneComponent>(this);
	character.assign<plague::Transform>(plague::level01::player, 0.15f);  // position and scale
	character.assign<plague::Sprite>("img/character/character.png", true, false);
	character.assign<plague::CharacterComponent>(character.id(), 250.0f);
	character.assign<plague::CountSensorComponent>();
	character.assign<plague::TimerComponent>("fire", 3);
	// character.assign<plague::BrainComponent>(character.id(), "brain");

	auto character2 = ex.entities.create();
	character2.assign<plague::SceneComponent>(this);
	character2.assign<plague::Transform>(plague::level01::player, 0.30f);  // position and scale
	character2.assign<plague::Sprite>("img/character/character.png", true, false);
	character2.assign<plague::CharacterComponent>(character2.id(), 100.0f);
	character2.assign<plague::CountSensorComponent>();
	character2.assign<plague::BrainComponent>(character2.id(), "brain2");

	auto character3 = ex.entities.create();
	character3.assign<plague::SceneComponent>(this);
	character3.assign<plague::Transform>(plague::level01::player, 0.21f);  // position and scale
	character3.assign<plague::Sprite>("img/character/character.png", true, false);
	character3.assign<plague::CharacterComponent>(character3.id(), 200.0f);
	character3.assign<plague::CountSensorComponent>();
	character3.assign<plague::BrainComponent>(character3.id(), "brain3");

	ex.systems.add<plague::MovementSystem>();
	ex.systems.add<plague::InputSystem>(this, character.id());
	ex.systems.add<plague::AutoDestroySystem>();
	ex.systems.add<plague::CountDownSystem>(3);
	// director de oleadas
	ex.systems.add<plague::BlackboardSystem>();
	// personaje
	ex.systems.add<plague::CharacterSystem>();
	// detecci�n superior (fuera de mapa)
	ex.systems.add<plague::DetectInvasionSystem>();
	// detecci�n inferior (fuera de mapa)
	ex.systems.add<plague::DetectFloorImpactSystem>();
	// sistema f�sico
	ex.systems.add<plague::PhysicsSystem>(this);
	// generador de f�sica
	ex.systems.add<plague::PhysicsBuilderSystem>();
	// actualizar IA
	ex.systems.add<plague::BrainSystem>();
	// Steering behaviours system
	ex.systems.add<plague::SteeringBehavioursSystem>();
	ex.systems.add<plague::SpriteSystem>();
	ex.systems.add<plague::CountSensorSystem>();
	ex.systems.add<plague::TimerSystem>();
	ex.systems.configure();

    return true;
}


void Level01::render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection)
{
	cocos2d::Scene::render(renderer, eyeTransform, eyeProjection);
	ex.systems.update_all(1.0f / 60.0f);
}

