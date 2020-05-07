//
// Sistema de entrada (teclado/raton/touch)
//
#pragma once
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "RightCommand.h"
#include "LeftCommand.h"
#include "MouseMoveCommand.h"
#include "utils.h"
#include "AutoDestroyDescription.h"
#include "FireCommand.h"
#include "ExitGameCommand.h"
#include "MainMenuScene.h"
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif
// Navmesh
#include "navmesh/CCNavMesh.h"
#include "3d/CCBundle3D.h"
#include "physics3d/CCPhysics3D.h"
#include "physics3d/CCPhysics3DWorld.h"

namespace plague {

template <
	class Key,
	class Value,
	class Comparator = typename std::map<Key, Value>::key_compare,
	class Allocator = typename std::map<Key, Value>::allocator_type
>
class DefaultDict : public std::map<Key, Value, Comparator, Allocator>
{
public:
	Value& at(const Key& key) {
		return std::map<Key, Value, Comparator, Allocator>::operator[](key);
	}
};

struct InputSystem : public entityx::System<InputSystem>,
					 public entityx::Receiver<InputSystem>,
					 public cocos2d::Node  // TODO: remove, used by "convertToNodeSpace"
{
	explicit InputSystem(cocos2d::Scene* scene, entityx::Entity::Id player_to_control)
		: _scene(scene)
		, _player_to_control(player_to_control)
		, _touching(false)
		, _moved(false)
		
	{
		_listener = cocos2d::EventListenerKeyboard::create();
		_listener->retain();
		_listener->onKeyPressed = CC_CALLBACK_2(InputSystem::onKeyPressed, this);
		_listener->onKeyReleased = CC_CALLBACK_2(InputSystem::onKeyReleased, this);

		_listener_touch = cocos2d::EventListenerTouchOneByOne::create();
		_listener_touch->retain();
		_listener_touch->onTouchBegan = CC_CALLBACK_2(InputSystem::onTouchBegan, this);
		_listener_touch->onTouchMoved = CC_CALLBACK_2(InputSystem::onTouchMoved, this);
		_listener_touch->onTouchEnded = CC_CALLBACK_2(InputSystem::onTouchEnded, this);

		_listener_mouse = cocos2d::EventListenerMouse::create();
		_listener_mouse->retain();
		_listener_mouse->onMouseMove = CC_CALLBACK_1(InputSystem::onMouseMove, this);
		_listener_mouse->onMouseUp = CC_CALLBACK_1(InputSystem::onMouseUp, this);
		_listener_mouse->onMouseDown = CC_CALLBACK_1(InputSystem::onMouseDown, this);
		_listener_mouse->onMouseScroll = CC_CALLBACK_1(InputSystem::onMouseScroll, this);

		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, _scene);
		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener_touch, _scene);
		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener_mouse, _scene);




		using namespace cocos2d;

		std::vector<Vec3> trianglesList = Bundle3D::getTrianglesList("grid/grid.obj");
		Physics3DRigidBodyDes rbDes;
		rbDes.mass = 0.0f;
		rbDes.shape = Physics3DShape::createMesh(&trianglesList[0], (int)trianglesList.size() / 3);
		auto rigidBody = Physics3DRigidBody::create(&rbDes);
		auto component = Physics3DComponent::create(rigidBody);
		auto sprite = Sprite3D::create("grid/grid.obj");
		sprite->addComponent(component);
		sprite->setCameraMask((unsigned short)CameraFlag::USER1);
		_scene->addChild(sprite);


		cocos2d::Size size = cocos2d::Director::getInstance()->getWinSize();
		_camera = cocos2d::Camera::createPerspective(60.0f, size.width / size.height, 1.0f, 1000.0f);
		// _camera = cocos2d::Camera::createOrthographic(50, 50, 1, 1000);
		// _camera->setViewport(experimental::Viewport(0, 0, 1080, 1920));
		_camera->setPosition3D(cocos2d::Vec3(.0f, 20.0f, 20.0f));
		_camera->lookAt(cocos2d::Vec3(0.0f, 0.0f, 0.0f), cocos2d::Vec3(0.0f, 1.0f, 0.0f));
		_camera->setCameraFlag(cocos2d::CameraFlag::USER1);
		_scene->addChild(_camera);

		navmesh = cocos2d::NavMesh::create("grid/all_tiles_tilecache.bin", "grid/grid.gset");
		navmesh->setDebugDrawEnable(true);

		_scene->setNavMesh(navmesh);
		_scene->setNavMeshDebugCamera(_camera);

		auto ambientLight = cocos2d::AmbientLight::create(cocos2d::Color3B(64, 64, 64));
		ambientLight->setCameraMask((unsigned short)cocos2d::CameraFlag::USER1);
		_scene->addChild(ambientLight);

		auto dirLight = DirectionLight::create(Vec3(1.2f, -1.1f, 0.5f), cocos2d::Color3B(255, 255, 255));
		dirLight->setCameraMask((unsigned short)cocos2d::CameraFlag::USER1);
		_scene->addChild(dirLight);

		// create obstable
		for(int j=2; j<8; j+=4)
		{
			for(int i=-3; i<5; i++)
			{
				cocos2d::Vec3 pos(i, 1, j - 1);
				auto obstacle = cocos2d::NavMeshObstacle::create(0.5f, 2.0f);
				auto obstacleNode = cocos2d::Sprite3D::create("grid/cylinder.obj");
				obstacleNode->setPosition3D(pos);
				// obstacleNode->setRotation3D(Vec3(-90.0f, 0.0f, 0.0f));
				// obstacleNode->setScale(0.1f);
				obstacleNode->addComponent(obstacle);
				obstacleNode->setCameraMask((unsigned short)CameraFlag::USER1);
				obstacleNode->setVisible(false);
				_scene->addChild(obstacleNode);

				// navmesh->addNavMeshObstacle(obstacle);
			}

			for(int i=-5; i<3; i++)
			{
				cocos2d::Vec3 pos(i, 1, j + 1);
				auto obstacle = cocos2d::NavMeshObstacle::create(0.5f, 2.0f);
				auto obstacleNode = cocos2d::Sprite3D::create("grid/cylinder.obj");
				obstacleNode->setPosition3D(pos);
				// obstacleNode->setRotation3D(Vec3(-90.0f, 0.0f, 0.0f));
				// obstacleNode->setScale(0.1f);
				obstacleNode->addComponent(obstacle);
				obstacleNode->setCameraMask((unsigned short)CameraFlag::USER1);
				obstacleNode->setVisible(false);
				_scene->addChild(obstacleNode);
			}
		}
		
		// create agents
		{
			cocos2d::Vec3 posAgent(-3, 1, -3);
			cocos2d::NavMeshAgentParam param;
			param.radius = 0.5f;
			param.height = 1.8f;
			param.maxSpeed = 2.0f;
			param.maxAcceleration = 1000.0f;
			agent = NavMeshAgent::create(param);
			auto agentNode = cocos2d::Sprite3D::create("grid/cylinder.obj");
			agentNode->setPosition3D(posAgent);
			// agentNode->setRotation3D(Vec3(-90.0f, 0.0f, 0.0f));
			// agentNode->setScale(0.1f);
			agentNode->addComponent(agent);
			agentNode->setCameraMask((unsigned short)CameraFlag::USER1);
			agentNode->setVisible(false);
			_scene->addChild(agentNode);
		}








	}

	virtual ~InputSystem()
	{
		_scene->getEventDispatcher()->removeEventListener(_listener);
		_scene->getEventDispatcher()->removeEventListener(_listener_touch);
		_scene->getEventDispatcher()->removeEventListener(_listener_mouse);
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		events.subscribe<plague::ExitGameCommand>(*this);
	}

	void receive(const plague::ExitGameCommand& event)
	{
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFadeTR::create(1, MainMenuScene::create()));
		// cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(2, MainMenuScene::create()));
		// cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
	}

	////////////////////////////////////////////////////////////////////////

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		_mappingPrevious[keyCode] = _mapping[keyCode];
		_mapping[keyCode] = true;
	}

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		_mappingPrevious[keyCode] = _mapping[keyCode];
		_mapping[keyCode] = false;
	}

	////////////////////// TOUCH EVENTS /////////////////////////////////////

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* e)
	{
		_touching = true;

		// read touch position
		cocos2d::Vec2 touchLocation = touch->getLocationInView();
		touchLocation = cocos2d::Director::getInstance()->convertToGL(touchLocation);
		touchLocation = convertToNodeSpace(touchLocation);

		_mouse_x = touchLocation.x;
		_mouse_y = touchLocation.y;

		// auto touch = touches[0];
		auto location = touch->getLocationInView();
		cocos2d::Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);

		auto size = cocos2d::Director::getInstance()->getWinSize();
		_camera->unproject(size, &nearP, &nearP);
		_camera->unproject(size, &farP, &farP);

		cocos2d::Physics3DWorld::HitResult result;
		_scene->getPhysics3DWorld()->rayCast(nearP, farP, &result);
		agent->move(result.hitPosition);
		std::cout << "hit = " << result.hitPosition.x << ", " << result.hitPosition.y << ", " << result.hitPosition.z << std::endl;

		return true;
	}

	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* e)
	{
		;
	}

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* e)
	{
		_touching = false;
	}

	/////////////////////// 

	void onMouseDown(cocos2d::EventMouse* e)
	{
		_mouse_x = e->getCursorX();
		_mouse_y = e->getCursorY();
	}

	void onMouseUp(cocos2d::EventMouse* e)
	{
		;
	}

	void onMouseMove(cocos2d::EventMouse* e)
	{
		_moved = true;
		_mouse_x = e->getCursorX();
		_mouse_y = e->getCursorY();
	}

	void onMouseScroll(cocos2d::EventMouse* e)
	{

	}

	//////////////////////////////////////////////////////////////////////////////////////////

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		bool value;

		// on_change
		value = _mapping[EventKeyboard::KeyCode::KEY_D];
		if (value != _mappingPrevious[EventKeyboard::KeyCode::KEY_D])
		{
			events.emit<plague::RightCommand>(_player_to_control, _player_to_control, value);
		}

		// on_change
		value = _mapping[EventKeyboard::KeyCode::KEY_A];
		if (value != _mappingPrevious[EventKeyboard::KeyCode::KEY_A])
		{
			events.emit<plague::LeftCommand>(_player_to_control, _player_to_control, value);
		}

		// on_move
		if (_moved)
		{
			events.emit<plague::MouseMoveCommand>(_mouse_x, _mouse_y);
			_moved = false;
		}

		// on_press
		if (_mapping[EventKeyboard::KeyCode::KEY_SPACE])
		{
			events.emit<plague::FireCommand>(_player_to_control, _player_to_control);
			_mapping[EventKeyboard::KeyCode::KEY_SPACE] = false;
		}

#else
		if (_touching)
		{
			auto quinto = cocos2d::Director::getInstance()->getVisibleSize().width / 5;
			if (_mouse_x > (4*quinto))
			{
				events.emit<plague::RightCommand>(_player_to_control, _player_to_control, true);
			}
			else if (_mouse_x < quinto)
			{
				events.emit<plague::LeftCommand>(_player_to_control, _player_to_control, true);
			}
			else
			{
				events.emit<plague::FireCommand>(_player_to_control, _player_to_control);
				_touching = false;  // avoid autofire
			}
		}
		else
		{
			events.emit<plague::RightCommand>(_player_to_control, _player_to_control, false);
			events.emit<plague::LeftCommand>(_player_to_control, _player_to_control, false);
		}
#endif
		if (_mapping[EventKeyboard::KeyCode::KEY_ESCAPE] || _mapping[EventKeyboard::KeyCode::KEY_BACK])
		{
			events.emit<plague::ExitGameCommand>();
			_mapping[EventKeyboard::KeyCode::KEY_ESCAPE] = false;
			_mapping[EventKeyboard::KeyCode::KEY_BACK] = false;
		}
	};

protected:
	cocos2d::Scene* _scene;
	entityx::Entity::Id _player_to_control;

	cocos2d::EventListenerKeyboard* _listener;
	cocos2d::EventListenerTouchOneByOne* _listener_touch;
	cocos2d::EventListenerMouse* _listener_mouse;

	DefaultDict<cocos2d::EventKeyboard::KeyCode, bool> _mappingPrevious;
	DefaultDict<cocos2d::EventKeyboard::KeyCode, bool> _mapping;

	float _mouse_x;
	float _mouse_y;

	bool _touching;
	bool _moved;

	// NavMesh
	cocos2d::NavMesh* navmesh;
	cocos2d::Camera *_camera;
	cocos2d::NavMeshAgent* agent;
};

}

#endif
