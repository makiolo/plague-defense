#include "Level01.h"
#include "Level01Constants.h"
//
#include "entityx/entityx.h"
#include "PhysicsShapeCache.h"

// COMPONENT
#include "Sprite.h"
#include "Transform.h"
#include "DebugBar.h"
#include "CharacterComponent.h"
#include "BrainComponent.h"
#include "CountSensorComponent.h"
#include "SceneComponent.h"
#include "TimerComponent.h"
#include "LayerColorComponent.h"
#include "ParticleFireWorksComponent.h"
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
#include "AnimationSystem.h"

// SCENES
#include "MainMenuScene.h"
// SPAWNERS
#include "utils.h"
// Networking
#include <network/WebSocket.h>
// Publicidad
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif
// AI
#include "myBT/myBT.h"
// Sounds
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d;
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
	//delete websocket;
}


Scene* Level01::createScene()
{
    return Level01::create();
}

bool Level01::init()
{
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

	// auto sky = ex.entities.create();
	// sky.assign<plague::SceneComponent>(this, -2);
	// sky.assign<plague::Transform>(cocos2d::Vec2::ZERO, 1.0f);
	// sky.assign<plague::LayerColorCompomnent>();

	auto building = ex.entities.create();
	building.assign<plague::SceneComponent>(this);
	building.assign<plague::Transform>(cocos2d::Vec2::ZERO, 1.0f);  // position and scale
	building.assign<plague::Sprite>("img/building/newlevel01.png", 128, true, true);

	auto scenary = ex.entities.create();
	scenary.assign<plague::DebugBar>(this, ex.events);

	auto character = ex.entities.create();
	character.assign<plague::SceneComponent>(this);
	character.assign<plague::Transform>(plague::level01::player, 0.15f);  // position and scale
	character.assign<plague::Sprite>("img/character/character.png", 255, true, false);
	character.assign<plague::CharacterComponent>(character.id(), 250.0f);
	character.assign<plague::CountSensorComponent>();
	character.assign<plague::ParticleFireworksCompomnent>( character.id() );
	//character.assign<plague::TimerComponent>("fire", 3);
	// character.assign<plague::BrainComponent>(character.id(), "brain");

	// auto character2 = ex.entities.create();
	// character2.assign<plague::SceneComponent>(this);
	// character2.assign<plague::Transform>(plague::level01::player, 0.30f);  // position and scale
	// character2.assign<plague::Sprite>("img/character/character.png", true, false);
	// character2.assign<plague::CharacterComponent>(character2.id(), 100.0f);
	// character2.assign<plague::CountSensorComponent>();
	// character2.assign<plague::BrainComponent>(character2.id(), "brain2");

	// auto character3 = ex.entities.create();
	// character3.assign<plague::SceneComponent>(this);
	// character3.assign<plague::Transform>(plague::level01::player, 0.21f);  // position and scale
	// character3.assign<plague::Sprite>("img/character/character.png", true, false);
	// character3.assign<plague::CharacterComponent>(character3.id(), 200.0f);
	// character3.assign<plague::CountSensorComponent>();
	// character3.assign<plague::BrainComponent>(character3.id(), "brain3");

	// https://www.freecodecamp.org/news/an-embarrassing-tale-why-my-server-could-only-handle-10-players-3b83b6fa8136/
	// https://sergiodxa.com/articles/scalable-real-time-applications/
	//websocket = new network::WebSocket();
	//websocket->init(*this, "ws://broker.hivemq.com:8000");

	/*
	
	IA da ordees Seek/Flee ---> Al CharacterController
	Character da controles de usuario (izquierda, derecha), imitando a su fantasma IA, o el humano directamente al AnimationController
	El AnimationController elige la mejor animación que cumple con el comando --> Finalmente cada animación aplica el movimiento asociado

	La curva de movimiento, en lugar de ser Lineal, podriamos utilizar las curvas Skew de Cocos

	Animación: Andar     VelMax:   20        AccMax: 1000        Curva: Senoidal       Direccion:  (0, 0, -1)         Duración: 3s          Distancia: 5 metros
	Animación: Salto     VelMax:   20        AccMax: 1000        Curva: Senoidal       Direccion:  (0, 0, -1)         Duración: 3s          Distancia: 5 metros

	*/
	//
	// Dragonbones tiene eventos de sonido y eventos custom, probarlos.
	// https://github.com/DragonBones/DragonBonesCPP/tree/master/Cocos2DX_3.x/src/dragonBones/cocos2dx
	//


	// PhysicsShapeCache::getInstance();

	/*
	Shaders:
	https://github.com/urho3d/Urho3D/tree/master/bin/CoreData/Shaders/GLSL
	https://github.com/phi-lira/UniversalShaderExamples/blob/b450133fedf51ab3e1944fc630eb1f5954c4c55a/Assets/_ExampleScenes/51_LitPhysicallyBased/CustomLit.shader
	https://github.com/phi-lira/UniversalShaderExamples/blob/b450133fedf51ab3e1944fc630eb1f5954c4c55a/Assets/_ExampleScenes/CustomShading.hlsl
	https://github.com/urho3d/Urho3D/blob/17c4a1022d3342b6318fa095661a0ecba6306284/bin/CoreData/Shaders/GLSL/PBRDeferred.glsl
	https://www.youtube.com/watch?v=0ckE-CZpXAo
	https://www.youtube.com/watch?v=7hxrPKoELpo
	*/



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
	ex.systems.add<plague::AnimationSystem>();
	ex.systems.configure();

    return true;
}


void Level01::render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection)
{
	cocos2d::Scene::render(renderer, eyeTransform, eyeProjection);
	ex.systems.update_all(1.0f / 60.0f);
}

void Level01::onOpen(cocos2d::network::WebSocket* ws)
{
	std::cout << "pause" << std::endl;
}

void Level01::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) 
{
	std::cout << "pause" << std::endl;
}

void Level01::onClose(cocos2d::network::WebSocket* ws) 
{
	std::cout << "pause" << std::endl;
}

void Level01::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) 
{
	std::cout << "pause" << std::endl;
}


