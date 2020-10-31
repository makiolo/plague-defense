#include "Level01.h"
#include "engine/scene/constants/Level01Constants.h"
//
#include "entityx/entityx.h"
#include "engine/thirdparty/physics/PhysicsShapeCache.h"

// COMPONENT
#include "engine/component/2d/Sprite2DComponent.h"
#include "engine/component/Transform.h"
#include "engine/component/debug/ConsoleComponent.h"
#include "engine/component/character/CharacterComponent.h"
#include "engine/component/ai/brain/BrainComponent.h"
#include "engine/component/ai/sensor/EnemyCountSensorComponent.h"
#include "engine/component/SceneComponent.h"
#include "engine/component/TimerComponent.h"
#include "engine/component/2d/LayerColorComponent.h"
#include "engine/component/2d/ParticleFireWorksComponent.h"
#include "engine/component/2d/SpriterModelComponent.h"
#include "engine/component/3d/Sprite3DComponent.h"
#include "engine/component/3d/NavMeshComponent.h"
#include "engine/component/3d/NavMeshAgentComponent.h"
#include "engine/component/3d/NavMeshObstacleComponent.h"
#include "engine/component/ui/LabelWithTTFUIComponent.h"
#include "engine/component/3d/CameraComponent.h"
// SYSTEMS
#include "engine/system/CloudSystem.h"
#include "engine/system/InputSystem.h"
#include "engine/system/AutoDestroySystem.h"
#include "engine/system/CountdownSystem.h"
#include "engine/system/BlackBoardSystem.h"
#include "engine/system/DetectInvasionSystem.h"
#include "engine/system/CharacterSystem.h"
#include "engine/system/DetectFloorImpactSystem.h"
#include "engine/system/PhysicsSystem.h"
#include "engine/system/builder/PhysicsBuilderSystem.h"
#include "engine/system/BrainSystem.h"
#include "engine/system/SteeringBehavioursSystem.h"
#include "engine/system/CocosGeneratorSystem.h"
#include "engine/system/sensor/EnemyCountSensorSystem.h"
#include "engine/system/TimerSystem.h"
#include "engine/system/sensor/ProjectilCountSensorSystem.h"

// SCENES
#include "MainMenuScene.h"
// SPAWNERS
#include "engine/prefabs/utils.h"
// Networking
#include <network/WebSocket.h>
// Publicidad
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif
// AI
#include "myBT/myBT.h"
// Sound
#include "audio/include/AudioEngine.h"

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

	AudioEngine::pauseAll();
	AudioEngine::play2d("sounds/birds.mp3");

	// plague::make_clouds(this, ex.entities);

	auto sky = ex.entities.create();
	sky.assign<plague::SceneComponent>(this);
	sky.assign<plague::Transform>(cocos2d::Vec2::ZERO, 1.0f);
	sky.assign<plague::LayerColorCompomnent>(255);

	auto building = ex.entities.create();
	building.assign<plague::SceneComponent>(this, 1);
	building.assign<plague::Transform>(cocos2d::Vec2::ZERO, 1.0f);
	building.assign<plague::Sprite2DComponent>("img/building/newlevel01.png", 255, cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);

    auto debugbar = ex.entities.create();
    // todo: add scenecomponent
    debugbar.assign<plague::ConsoleComponent>(this, ex.events);

	// Gestión textos
	auto scenary = ex.entities.create();
	scenary.assign<plague::SceneComponent>(this);
	scenary.assign<plague::Transform>(cocos2d::Vec2(800, 200), 2.5f);  // position and scale
	scenary.assign<plague::Sprite2DComponent>("gui/bocadillo.png", 255, cocos2d::Vec2::ANCHOR_MIDDLE, cocos2d::Vec2(0, -12), 0.3f);
	scenary.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(128, 128, 128, 255), "Hola mundo", 32);


	auto character = ex.entities.create();
	character.assign<plague::SceneComponent>(this, 2);
	character.assign<plague::Transform>(plague::level01::player, 1.0f);  // position and scale
	auto character_comp = character.assign<plague::CharacterComponent>(character.id(), 250.0f);
	auto spriter_comp = character.assign<plague::SpriterModelComponent>("spriterpro/GreyGuy/player.scml", "Player", "flip");
    character_comp->setSpriter(spriter_comp.get());


	auto character2 = ex.entities.create();
	character2.assign<plague::SceneComponent>(this, 2);
	character2.assign<plague::Transform>(plague::level01::player, 0.30f);  // position and scale
	character2.assign<plague::Sprite2DComponent>("img/character/character.png", 255, cocos2d::Vec2(0.5, 0.0));
	character2.assign<plague::CharacterComponent>(character2.id(), 250.0f, false);
	character2.assign<plague::EnemyCountSensorComponent>();
	character2.assign<plague::BrainComponent>("brain2");


	// auto character3 = ex.entities.create();
	// character3.assign<plague::SceneComponent>(this);
	// character3.assign<plague::Transform>(plague::level01::player, 0.21f);  // position and scale
	// character3.assign<plague::Sprite2DComponent>("img/character/character.png", true, false);
	// character3.assign<plague::CharacterComponent>(character3.id(), 200.0f);
	// character3.assign<plague::EnemyCountSensorComponent>();
	// character3.assign<plague::BrainComponent>("brain3");



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

	ex.systems.add<plague::CloudSystem>();
	ex.systems.add<plague::InputSystem>(this, character.id());
	ex.systems.add<plague::AutoDestroySystem>();
	ex.systems.add<plague::CountDownSystem>(3);
	ex.systems.add<plague::BlackboardSystem>();
	ex.systems.add<plague::CharacterSystem>();
	ex.systems.add<plague::DetectInvasionSystem>();
	ex.systems.add<plague::DetectFloorImpactSystem>();
	ex.systems.add<plague::PhysicsSystem>(this);
	ex.systems.add<plague::PhysicsBuilderSystem>();
	ex.systems.add<plague::BrainSystem>(this);
	ex.systems.add<plague::SteeringBehavioursSystem>();
	ex.systems.add<plague::CocosGeneratorSystem>();
	ex.systems.add<plague::TimerSystem>();
    ex.systems.add<plague::EnemyCountSensorSystem>();
    ex.systems.add<plague::ProjectilCountSensorSystem>();
	ex.systems.configure();

    return true;
}


void Level01::render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection)
{
	cocos2d::Scene::render(renderer, eyeTransform, eyeProjection);
	ex.systems.update_all(1.0f / 60.0f);
}

