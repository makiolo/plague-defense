//
// Sistema de entrada (teclado/raton/touch)
//
#pragma once
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/event/character/RightCommand.h"
#include "engine/event/character/LeftCommand.h"
#include "engine/prefabs/utils.h"
#include "engine/component/descriptor/AutoDestroyDescription.h"
#include "engine/event/character/FireCommand.h"
#include "engine/event/ExitGameEvent.h"
#include "engine/scene/MainMenuScene.h"
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif
// Navmesh
#include "navmesh/CCNavMesh.h"
#include "3d/CCBundle3D.h"
#include "physics3d/CCPhysics3D.h"
#include "physics3d/CCPhysics3DWorld.h"
#include "renderer/backend/Device.h"

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
					 public entityx::Receiver<InputSystem>
{
	explicit InputSystem(cocos2d::Scene* scene, entityx::Entity::Id player_to_control)
		: _scene(scene)
		, _player_to_control(player_to_control)
		, _touching(false)
		, _spawn_agent(true)
	{
		_listener = cocos2d::EventListenerKeyboard::create();
		_listener->onKeyPressed = CC_CALLBACK_2(InputSystem::onKeyPressed, this);
		_listener->onKeyReleased = CC_CALLBACK_2(InputSystem::onKeyReleased, this);

		_listener_touch = cocos2d::EventListenerTouchOneByOne::create();
		_listener_touch->onTouchBegan = CC_CALLBACK_2(InputSystem::onTouchBegan, this);
		_listener_touch->onTouchMoved = CC_CALLBACK_2(InputSystem::onTouchMoved, this);
		_listener_touch->onTouchEnded = CC_CALLBACK_2(InputSystem::onTouchEnded, this);

		_listener_mouse = cocos2d::EventListenerMouse::create();
		_listener_mouse->onMouseMove = CC_CALLBACK_1(InputSystem::onMouseMove, this);
		_listener_mouse->onMouseUp = CC_CALLBACK_1(InputSystem::onMouseUp, this);
		_listener_mouse->onMouseDown = CC_CALLBACK_1(InputSystem::onMouseDown, this);
		_listener_mouse->onMouseScroll = CC_CALLBACK_1(InputSystem::onMouseScroll, this);

		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, _scene);
		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener_touch, _scene);
		_scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener_mouse, _scene);

		
		/*
		 * NavMesh:
		 * 
		 * 	Sprite3D
		 * 			Physics3DShape
		 * 			Physics3DComponent
		 * 	Material
		 * 	Camera
		 *  SceneComponent (Sin Transform)
		 * 	NavMesh
		 */ 
		/*
			Obstaculo:
				SceneComponent
				Transdorm
				Sprite3D
				NavMeshObstacle (Componente de Sprite3D)
		*/
		/*
			Agente:
				SceneComponent
				Transform
				Sprite3D
				NavMeshAgent (Componente de Sprite3D)
		*/
#if 0
		using namespace cocos2d;

		//////////////////////////////

		// resource obj
		// position sprite 3d


        auto building = Sprite3D::create("buildings/building.c3b");
        building->setPosition3D(cocos2d::Vec3(0,0,-10));
        building->setCameraMask((unsigned short)CameraFlag::USER1);
        _scene->addChild(building);


		auto sprite = Sprite3D::create("grid/grid.c3b");
		sprite->setPosition3D(cocos2d::Vec3(0,0,-10));
		sprite->setCameraMask((unsigned short)CameraFlag::USER1);
		_scene->addChild(sprite);

        //////////////////////////////

        // resource obj <-------- from sprite 3d

        Physics3DRigidBodyDes rbDes;
        {
            std::vector<Vec3> trianglesList = Bundle3D::getTrianglesList("grid/grid.c3b");
            rbDes.mass = 0.0f;
            rbDes.shape = Physics3DShape::createMesh(&trianglesList[0], (int)trianglesList.size() / 3);
        }
        auto rigidBody = Physics3DRigidBody::create(&rbDes);
        auto component = Physics3DComponent::create(rigidBody);
        sprite->addComponent(component);

        //////////////////////////////

		cocos2d::Size size = cocos2d::Director::getInstance()->getWinSize();

		// Create Camera3D

		_camera = cocos2d::Camera::create();
		_camera->setPosition3D(cocos2d::Vec3(0.0f, 150.5f, 10.5f));
		_camera->lookAt(cocos2d::Vec3(0.0f, 0.0f, -10.0f), cocos2d::Vec3(0.0f, 0.0f, -1.0f));
		_camera->setCameraFlag(cocos2d::CameraFlag::USER1);
		_scene->addChild(_camera);

		////////////////////////////////

		navmesh = cocos2d::NavMesh::create("grid/grid2_all_tiles_tilecache.bin", "grid/grid2.gset");
		navmesh->setAreaCost(NAVMESH_AREA_GROUND, 1.0f);
		navmesh->setAreaCost(NAVMESH_AREA_WATER, 1.0f);
		navmesh->setAreaCost(NAVMESH_AREA_ROAD, 1.0f);
		navmesh->setAreaCost(NAVMESH_AREA_DOOR, 1.0f);
		navmesh->setAreaCost(NAVMESH_AREA_GRASS, 1.0f);
		navmesh->setAreaCost(NAVMESH_AREA_JUMP, 1.0f);
		navmesh->setIncludeFlags(NAVMESH_FLAG_WALK | NAVMESH_FLAG_SWIM);
		navmesh->setExcludeFlags(0);

		_scene->setNavMesh(navmesh);

		const bool debug_navmesh = false;
		navmesh->setDebugDrawEnable(debug_navmesh);
		if(debug_navmesh)
		{
			_scene->setNavMeshDebugCamera(_camera);

			auto ambientLight = cocos2d::AmbientLight::create(cocos2d::Color3B(64, 64, 64));
			ambientLight->setCameraMask((unsigned short)cocos2d::CameraFlag::USER1);
			_scene->addChild(ambientLight);

			auto dirLight = DirectionLight::create(Vec3(1.2f, -1.1f, 0.5f), cocos2d::Color3B(255, 255, 255));
			dirLight->setCameraMask((unsigned short)cocos2d::CameraFlag::USER1);
			_scene->addChild(dirLight);
		}

        pointLight = PointLight::create(Vec3(2.2f, 5.0f, 2.5f), cocos2d::Color3B(255, 255, 255), 30000.0f);
        pointLight->setCameraMask((unsigned short)cocos2d::CameraFlag::USER1);
        pointLight->setLightFlag(LightFlag::LIGHT0);
        _scene->addChild(pointLight);


        // Crear materiales despues de crear luces
        material = cocos2d::Material::createWithFilename("materials/navmesh.material");
        /*
        auto position = pointLight->getPosition3D();
        auto color = pointLight->getColor();
        auto range = pointLight->getRange();
        material->getTechniqueByIndex(0)->getPassByIndex(0)->setUniformPointLightPosition((const void*)&position, sizeof(cocos2d::Vec3));
        material->getTechniqueByIndex(0)->getPassByIndex(0)->setUniformPointLightColor((const void*)&color, sizeof(cocos2d::Vec3));
        material->getTechniqueByIndex(0)->getPassByIndex(0)->setUniformPointLightRangeInverse((const void*)&range, sizeof(float));
        */
        sprite->setMaterial(material);
        sprite->setLightMask((int)LightFlag::LIGHT0);
#endif
	}

	virtual ~InputSystem()
	{
		_scene->getEventDispatcher()->removeEventListener(_listener);
		_scene->getEventDispatcher()->removeEventListener(_listener_touch);
		_scene->getEventDispatcher()->removeEventListener(_listener_mouse);
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		events.subscribe<plague::ExitGameEvent>(*this);
	}

	void receive(const plague::ExitGameEvent& event)
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

		cocos2d::Vec2 location = touch->getLocationInView();

		_mouse_x = location.x;
		_mouse_y = location.y;

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		if(_spawn_agent)
		{
		    make_agent(location);
		    _spawn_agent = false;
		}
		else
        {
		    move_agent(location);
		    _spawn_agent = true;
        }
#endif

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

		//
		//		escribir en el 3d, utilizando coordenadas 2d (un area menor a la pantalla)
		//		leer del mundo 3d (un area menor al objeto 3d), y traerlo recibido en 2d
		//
		//		Funcionalidad a conseguir para traducir el navmesh a 2D.
		//

		cocos2d::Vec2 location = e->getLocation();

		//////////////////

		if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
		{
            make_agent(location);
        }
		else if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
		{
            move_agent(location);
        }
		else if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_4)
		{
            make_obstacle(location);
        }
	}

    void make_obstacle(const Vec2 &location) {
	    /*
        Obstaculo:
            SceneComponent
            Transdorm
            Sprite3D
            NavMeshObstacle (Componente de Sprite3D)
        */
        Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);

        auto size = Director::getInstance()->getWinSize();
        _camera->unproject(size, &nearP, &nearP);
        _camera->unproject(size, &farP, &farP);

        Physics3DWorld::HitResult result;
        _scene->getPhysics3DWorld()->rayCast(nearP, farP, &result);

        Vec3 pos = result.hitPosition;
        pos.y = 0.0f;
        auto obstacle = NavMeshObstacle::create(1.1f, 3.0f);
        auto obstacleNode = Sprite3D::create("grid/tower.obj");

        obstacleNode->setPosition3D(pos);
        obstacleNode->addComponent(obstacle);
        obstacleNode->setCameraMask((unsigned short) CameraFlag::USER1);

        auto material = Material::createWithFilename("materials/agent.material");
        obstacleNode->setMaterial(material);

        _scene->addChild(obstacleNode, 1);
    }

    void move_agent(const Vec2 &location)
    {
        Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);

        auto size = Director::getInstance()->getWinSize();
        _camera->unproject(size, &nearP, &nearP);
        _camera->unproject(size, &farP, &farP);

        Physics3DWorld::HitResult result;
        _scene->getPhysics3DWorld()->rayCast(nearP, farP, &result);

        NavMeshAgent::MoveCallback callback = [](NavMeshAgent *agent, float totalTimeAfterMove){

            if (agent->isOnOffMeshLink())
            {
                agent->setAutoTraverseOffMeshLink(false);
                agent->setAutoOrientation(false);

                OffMeshLinkData linkdata = agent->getCurrentOffMeshLinkData();

                agent->getOwner()->setPosition3D(linkdata.endPosition);
                agent->completeOffMeshLink();

                agent->setAutoTraverseOffMeshLink(true);
                agent->setAutoOrientation(true);
            }

            /*
            AgentUserData *data = static_cast<AgentUserData *>(agent->getUserData());
            if (agent->isOnOffMeshLink()){
                agent->setAutoTraverseOffMeshLink(false);
                agent->setAutoOrientation(false);
                OffMeshLinkData linkdata = agent->getCurrentOffMeshLinkData();

                agent->getOwner()->setPosition3D(jump(&linkdata.startPosition, &linkdata.endPosition, 10.0f, data->time));
                Vec3 dir = linkdata.endPosition - linkdata.startPosition;
                dir.y = 0.0f;
                dir.normalize();
                Vec3 axes;
                Vec3 refAxes = Vec3(-1.0f, 0.0f, 1.0f);
                refAxes.normalize();
                Vec3::cross(refAxes, dir, &axes);
                float angle = Vec3::dot(refAxes, dir);
                agent->getOwner()->setRotationQuat(Quaternion(axes, acosf(angle)));
                data->time += 0.01f;
                if (1.0f < data->time){
                    agent->completeOffMeshLink();
                    agent->setAutoOrientation(true);
                    data->time = 0.0f;
                }
            }
            */
        };

        for (auto& agent : agents)
        {
            agent->move(result.hitPosition, callback);
            //agent->move(result.hitPosition);
        }

        Vec3 testPoint(0.5f, 0.5f, 0.5f);

        /*
// https://metashapes.com/blog/opengl-metal-projection-matrix-problem/
Project
Punto en world space * getViewProjectionMatrix() (Projection * View)

local space = Local space
world matrix * local space = world space
view matrix * world matrix * local space = Camera space
projecttion matrix * view matrix * world matrix * local space = NDC Space (-1, +1)
GLviewport matrix * projecttion matrix * view matrix * world matrix * local space = GLviewport Space (0, 0, width, height)
OCOSviewport matrix * projecttion matrix * view matrix * world matrix * local space = COCOSViewport Space (0, 0, width, height)


world space -------> project() --------------> COCOSviewport space
world space -------> projectGL() ------------> GLviewport space


COCOSviewport space -----> unproject() ------> world space
GLviewport space -----> unprojectGL() -------> world space


Análisis de unproject():

COCOSViewport Space (0, 0, width, height)
a mano lo convierte en
NDC Space (-1, +1) = projecttion matrix * view matrix * world space
inversa projection matrix * NDC Space (-1, +1) = inversa projection matrix * projecttion matrix * view matrix * world space
inversa projection matrix * NDC Space (-1, +1) = view matrix * world space
inversa view matrix * inversa projection matrix * NDC Space (-1, +1) = inversa view matrix * view matrix * world space
inversa view matrix * inversa projection matrix * NDC Space (-1, +1) = world space

inversa view matrix * inversa projection matrix * NDC Space (-1, +1) = getViewProjectionMatrix().getInversed() * NDC Space (-1, +1)

getViewProjectionMatrix().getInversed() * NDC Space (-1, +1)


v^-1 * p^-1 * NDC Space
(projecttion matrix * view matrix)^-1 * NDC Space (-1, +1)


v^-1 * p^-1 = (p*v)^-1 ???

(AB)^-1 = B^-1 * A^-1


Falta ver los métodos del Director.

Nodo tiene los métodos para llegar a Local Space = (world matrix)^-1 * world space
*/

        // opengl screen space(1920x1080) -> cocos screen space(1920x1080)

        // de world space a viewport port space
        Vec2 projected = Director::getInstance()->getRunningScene()->getDefaultCamera()->project(testPoint);
        Vec2 projectedGL = Director::getInstance()->getRunningScene()->getDefaultCamera()->projectGL(testPoint);

        // De viewport space a world space
        Vec3 unprojected = Director::getInstance()->getRunningScene()->getDefaultCamera()->unproject(testPoint);
        Vec3 unprojectedGL = Director::getInstance()->getRunningScene()->getDefaultCamera()->unprojectGL(testPoint);

        Vec2 projected2 = _camera->project(testPoint);
        Vec2 projectedGL2 = _camera->projectGL(testPoint);
        Vec3 unprojected2 = _camera->unproject(testPoint);
        Vec3 unprojectedGL2 = _camera->unprojectGL(testPoint);
    }

    void make_agent(const Vec2 &location)
    {
	    /*
        Agente:
            SceneComponent
            Transform
            Sprite3D
            NavMeshAgent (Componente de Sprite3D)
        */
        Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);

        auto size = Director::getInstance()->getWinSize();
        _camera->unproject(size, &nearP, &nearP);
        _camera->unproject(size, &farP, &farP);

        Physics3DWorld::HitResult result;
        _scene->getPhysics3DWorld()->rayCast(nearP, farP, &result);
        Vec3 posAgent = result.hitPosition;
        posAgent.y = 0.0f;
        NavMeshAgentParam param;
        param.radius = 0.5f;
        param.height = 1.8f;
        param.maxSpeed = 8.0f;
        param.maxAcceleration = 1000.0f;
        param.queryFilterType = 0;
        auto agent = NavMeshAgent::create(param);
        agent->setAutoTraverseOffMeshLink(true);
        auto agentNode = Sprite3D::create("grid/cylinder.obj");
        agentNode->setPosition3D(posAgent);
        agentNode->addComponent(agent);
        agentNode->setCameraMask((unsigned short) CameraFlag::USER1);

        auto agent_material = Material::createWithFilename("materials/agent.material");
        /*
        auto position = pointLight->getPosition3D();
        auto color = pointLight->getColor();
        auto range = pointLight->getRange();
        agent_material->getTechniqueByIndex(0)->getPassByIndex(0)->setUniformPointLightPosition((const void*)&position, sizeof(cocos2d::Vec3));
        agent_material->getTechniqueByIndex(0)->getPassByIndex(0)->setUniformPointLightColor((const void*)&color, sizeof(cocos2d::Vec3));
        agent_material->getTechniqueByIndex(0)->getPassByIndex(0)->setUniformPointLightRangeInverse((const void*)&range, sizeof(float));
        */
        agentNode->setMaterial(agent_material);

        _scene->addChild(agentNode, 1);
        agents.push_back(agent);
    }

    void onMouseUp(cocos2d::EventMouse* e)
	{
		;
	}

	void onMouseMove(cocos2d::EventMouse* e)
	{
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
			events.emit<plague::ExitGameEvent>();
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

	// NavMesh
	cocos2d::NavMesh* navmesh;
	cocos2d::Camera* _camera;
	std::vector<cocos2d::NavMeshAgent*> agents;

	bool _spawn_agent;

    Material* material;
    PointLight* pointLight;
};

}

#endif
