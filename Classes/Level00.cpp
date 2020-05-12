#include "Level00.h"

#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif

USING_NS_CC;

Level00::Level00()
{

}

Level00::~Level00()
{
	
}

Scene* Level00::createScene()
{
	return Level00::create();
}

// on "init" you need to initialize your instance
bool Level00::init()
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
#endif

	// auto paraNode = ParallaxNode::create();
    //
	// auto fondo1 = Sprite::create("parallax/fondo1.png");
	// auto fondo2 = Sprite::create("parallax/fondo2.png");
	// auto fondo3 = Sprite::create("parallax/fondo3.png");
    //
	// // background image is moved at a ratio of 0.4x, 0.5y
	// paraNode->addChild(fondo1, -1, Vec2(0.4f, 0.5f), Vec2::ZERO);
    //
	// // tiles are moved at a ratio of 2.2x, 1.0y
	// paraNode->addChild(fondo2, 1, Vec2(2.2f, 1.0f), Vec2(0, -200));
    //
	// // top image is moved at a ratio of 3.0x, 2.5y
	// paraNode->addChild(fondo3, 2, Vec2(3.0f, 2.5f), Vec2(200, 800));
    //
	// this->addChild(paraNode, 1);


	/*
	auto building = ex->entities.create();
	plague::make_sprite(building, this, "img/building/level01.png", cocos2d::Vec2(850, 400), 0.8f);

	auto scenary = ex->entities.create();
	scenary.assign<plague::DebugBar>(this, ex->events);

	// plague::make_back_button(scenary, this, CC_CALLBACK_1(Level01::menuCloseCallback, this));

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
	ex->systems.add<plague::PhysicsBuilderSystem>();
	// Gravedad simulada
	ex->systems.configure();
	*/

	return true;
}


void Level00::render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection)
{
	
}
