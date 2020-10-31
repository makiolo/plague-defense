/* System class BrainSystem
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _BrainSystem_H_
#define _BrainSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "engine/component/ai/brain/BrainComponent.h"
#include "engine/component/ai/brain/SpiderBrainComponent.h"
#include "engine/component/2d/Sprite2DComponent.h"
#include "engine/component/Transform.h"
#include "engine/component/ai/sensor/EnemyCountSensorComponent.h"
#include "engine/component/ai/sensor/ProjectilCountSensorComponent.h"

namespace plague {

struct BrainSystem : public entityx::System<BrainSystem>
{
	explicit BrainSystem(cocos2d::Scene* scene)
	    : _scene(scene)
	{
			
	}

	virtual ~BrainSystem()
	{

	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
	    configure_brain2(es, events);
	    configure_spider(es, events);
	}

    void configure_brain2(entityx::EntityManager& es, entityx::EventManager& events)
    {
        std::string brain_name = "brain2";

        myBT::Parallel & bt = trees[brain_name];
        myBT::ConditionRepository & conditions = condition_map[brain_name];
        myBT::ActionRepository & actions = action_map[brain_name];

        // Actions
        actions["left"] = {
                [](myBT::Context& context) {
                    auto character = context.stack.get<CharacterComponent*>("character");
                    character->left(true);
                }, [](myBT::Context& context, double deltatime) {
                    return myBT::RUNNING;
                }, [](myBT::Context& context) {
                    auto character = context.stack.get<CharacterComponent*>("character");
                    character->left(false);
                }
        };
        actions["right"] = {
                [](myBT::Context& context) {
                    auto character = context.stack.get<CharacterComponent*>("character");
                    character->right(true);
                }, [](myBT::Context& context, double deltatime) {
                    return myBT::RUNNING;
                }, [](myBT::Context& context) {
                    auto character = context.stack.get<CharacterComponent*>("character");
                    character->right(false);
                }
        };
        actions["fire"] = {
                [](myBT::Context& context) {

                }, [](myBT::Context& context, double deltatime) {
                    auto character = context.stack.get<CharacterComponent*>("character");
                    auto count_sensor = context.stack.get<EnemyCountSensorComponent*>("count_sensor");
                    if (count_sensor->x != 0)
                    {
                        character->fire(true);
                    }
                    return myBT::COMPLETED;
                }, [](myBT::Context& context) {

                }
        };

        // Conditions
        conditions["left?"] = {
                [](myBT::Context& context, double deltatime) {
                    auto transform = context.stack.get<Transform*>("transform");
                    auto count_sensor = context.stack.get<EnemyCountSensorComponent*>("count_sensor");
                    if (count_sensor->x != 0)
                    {
                        double myposition = transform->get()->getPosition().x;
                        return myposition > (count_sensor->x + 10);
                    }
                    return false;
                }
        };
        conditions["right?"] = {
                [](myBT::Context& context, double deltatime) {
                    auto transform = context.stack.get<Transform*>("transform");
                    auto count_sensor = context.stack.get<EnemyCountSensorComponent*>("count_sensor");
                    if (count_sensor->x != 0)
                    {
                        double myposition = transform->get()->getPosition().x;
                        return myposition < (count_sensor->x - 10);
                    }
                    return false;
                }
        };
        conditions["has_enemies?"] = {
                [](myBT::Context& context, double deltatime) {
                    auto count_sensor = context.stack.get<EnemyCountSensorComponent*>("count_sensor");
                    return count_sensor->x != 0;
                }
        };

        /*
        while(true)
            if(pos.x > x)
                ir a la izquierda (while(no estoy en x))
            elif(pos.x < x)
                ir a la derecha (while(no estoy en x))
            else
                disparar
        */

        // Crear 2 bots pasandose el relevo para disparar
        // Prueba de sincronización


        // Para probar la mezcla de comportamiento scriptado con reactivo
        // Si no hay enemigos, patrullar

        auto fullpath = cocos2d::FileUtils::getInstance()->getWritablePath() + "/" + brain_name + ".json";

        if(cocos2d::FileUtils::getInstance()->isFileExist(fullpath))
        {

            // READ doctor.ai (default behaviour)
            bt.read_ai(fullpath, conditions, actions);

        }
        else
        {

            if(brain_name == "brain2")
            {

                auto selector_00 = bt.make_node<myBT::Selector>("main_control")->setPriority(true);

                    auto assert_00 = selector_00->make_node<myBT::Assert>("assert_00");

                        assert_00->make_node<myBT::Condition>("has_enemies?", conditions.at("has_enemies?"))->setInverse(true);

                        auto for_00 = assert_00->make_node<myBT::For>("for_00");

                            auto seq_00 = for_00->make_node<myBT::Sequence>("seq_00");

                                auto fortime_000 = seq_00->make_node<myBT::ForTime>("fortime_000")->setValueMin(0.5)->setValueMax(1.1);

                                    fortime_000->make_node<myBT::Action>("right", actions.at("right"));

                                auto fortime_001 = seq_00->make_node<myBT::ForTime>("fortime_001")->setValueMin(0.5)->setValueMax(1.1);

                                    fortime_001->make_node<myBT::Action>("left", actions.at("left"));

                    auto selector_01 = selector_00->make_node<myBT::Selector>("selector_01")->setPriority(true);

                        auto assert_01 = selector_01->make_node<myBT::Assert>("assert_01");

                            assert_01->make_node<myBT::Condition>("right?", conditions.at("right?"));
                            assert_01->make_node<myBT::Action>("right", actions.at("right"));

                        auto assert_02 = selector_01->make_node<myBT::Assert>("assert_02");

                            assert_02->make_node<myBT::Condition>("left?", conditions.at("left?"));
                            assert_02->make_node<myBT::Action>("left", actions.at("left"));

                        auto seq_02 = selector_01->make_node<myBT::Sequence>("seq_02");

                            seq_02->make_node<myBT::Action>("fire", actions.at("fire"));

                            auto fortime_002 = seq_02->make_node<myBT::ForTime>("fortime_002")->setValueMin(0.2)->setValueMax(0.6);

                                fortime_002->make_node<myBT::Running>("looking at stone");
            }
            else
            {
                // unknown IA
                std::abort();
            }

            bt.write_ai(fullpath, conditions, actions);
        }
    }

    void configure_spider(entityx::EntityManager& es, entityx::EventManager& events)
    {
        std::string brain_name = "spider";

        myBT::Parallel & bt = trees[brain_name];
        myBT::ConditionRepository & conditions = condition_map[brain_name];
        myBT::ActionRepository & actions = action_map[brain_name];

        // TODO: crear un steeringbehavioursSystem
        // Recibe peticiones de seek, flee, follow path, etc
        //
        //
        // TODO: usar el contexto para pasar parametros custom a las acciones
        // y así, tener un verdadero fly weight con el arbol compartido.
        //
        //
        // Comandos jugador:
        //				izq, der, y fire
        // Comandos torreta:
        //				Actualizarse, Venderla, Algoritmo de disparo
        // Especiales del jugador:
        //				Aceite hirviendo
        //
        //
        // Comandos enemigo
        //				izq, der, subir, bajar, esquivar
        //
        //
        //	Habilidades pasivas (ActiveSkillComponent):
        //				Aura de vida: cura aliados cercanos
        //				Division al morir
        //	Habilidades activas: (PassiveSkillComponent)
        //				Curar enemigos
        //
        //
        //	Condiciones para perder:
        //		- El jugador muere por cualquier causa
        //		- Pierdes todas las vidas -> Las estrellas se asignan en función de las vidas.
        //
        //
        //  Una habilidad depende de cierto sistema para funcionar.
        //  Chequear que esta instalado? por sanity ?
        //
        //
        //  Al principio todas las torretas son iguales, pero vas
        //  abriendo la niebla de las actualizaciones en cada partida
        //
        //

        actions["go_to_column1"] = {
                [&es, this](myBT::Context& context) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    const float velocity = 200.0f;
                    cocos2d::Vec2 pointA = transform->get()->getPosition();
                    cocos2d::Vec2 pointB(level01::column1, pointA.y);
                    float start_time = pointA.distance(pointB) / velocity;
                    transform->runAction(cocos2d::MoveBy::create(start_time, pointB - pointA));

                    entityx::Entity startA = es.create();
                    startA.assign<plague::SceneComponent>(this->_scene, 10);
                    startA.assign<plague::Transform>(pointA, 1.0f);  // position and scale
                    startA.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(255, 255, 28, 255), "A 1", 10, 1, cocos2d::Vec2(0, 20), 2.5f);
                    startA.assign<plague::AutoDestroyDescription>(3.0f);

                    entityx::Entity fireworks = es.create();
                    fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                    fireworks.assign<plague::Transform>(pointB, 1.0f);  // position and scale
                    fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(255, 25, 28, 255), "B 1", 10, 1, cocos2d::Vec2(0, 20), 2.5f);
                    fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                }, [&es, this](myBT::Context& context, double deltatime) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    if(transform->isDone()) {

                        entityx::Entity fireworks = es.create();
                        fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                        fireworks.assign<plague::Transform>(transform->get()->getPosition(), 1.0f);  // position and scale
                        fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(28, 255, 28, 255), "DONE 1", 10, 1, cocos2d::Vec2(0, 0), 2.5f);
                        fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                        return myBT::COMPLETED;
                    }
                    else
                        return myBT::RUNNING;
                }, [&es, this](myBT::Context& context) {

                    auto transform = context.stack.get<plague::Transform*>("transform");
                    entityx::Entity fireworks = es.create();
                    fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                    fireworks.assign<plague::Transform>(transform->get()->getPosition(), 1.0f);  // position and scale
                    fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(28, 255, 255, 255), "FIN 1", 10, 1, cocos2d::Vec2(0, -20), 2.5f);
                    fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                }
        };

        actions["go_to_column2"] = {
                [&es, this](myBT::Context& context) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    const float velocity = 200.0f;
                    cocos2d::Vec2 pointA = transform->get()->getPosition();
                    cocos2d::Vec2 pointB(level01::column2, pointA.y);
                    float start_time = pointA.distance(pointB) / velocity;
                    transform->runAction(cocos2d::MoveBy::create(start_time, pointB - pointA));

                    entityx::Entity startA = es.create();
                    startA.assign<plague::SceneComponent>(this->_scene, 10);
                    startA.assign<plague::Transform>(pointA, 1.0f);  // position and scale
                    startA.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(255, 255, 28, 255), "A 2", 10, 1, cocos2d::Vec2(0, 20), 2.5f);
                    startA.assign<plague::AutoDestroyDescription>(3.0f);

                    entityx::Entity fireworks = es.create();
                    fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                    fireworks.assign<plague::Transform>(pointB, 1.0f);  // position and scale
                    fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(255, 25, 28, 255), "B 2", 10, 1, cocos2d::Vec2(0, 20), 2.5f);
                    fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                }, [&es, this](myBT::Context& context, double deltatime) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    if(transform->isDone()) {

                        entityx::Entity fireworks = es.create();
                        fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                        fireworks.assign<plague::Transform>(transform->get()->getPosition(), 1.0f);  // position and scale
                        fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(28, 255, 28, 255), "DONE 2", 10, 1, cocos2d::Vec2(0, 0), 2.5f);
                        fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                        return myBT::COMPLETED;
                    }
                    else
                        return myBT::RUNNING;
                }, [&es, this](myBT::Context& context) {

                    auto transform = context.stack.get<plague::Transform*>("transform");
                    entityx::Entity fireworks = es.create();
                    fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                    fireworks.assign<plague::Transform>(transform->get()->getPosition(), 1.0f);  // position and scale
                    fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(28, 255, 255, 255), "FIN 2", 10, 1, cocos2d::Vec2(0, -20), 2.5f);
                    fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                }
        };

        actions["go_to_column3"] = {
                [&es, this](myBT::Context& context) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    const float velocity = 200.0f;
                    cocos2d::Vec2 pointA = transform->get()->getPosition();
                    cocos2d::Vec2 pointB(level01::column3, pointA.y);
                    float start_time = pointA.distance(pointB) / velocity;
                    transform->runAction(cocos2d::MoveBy::create(start_time, pointB - pointA));

                    entityx::Entity startA = es.create();
                    startA.assign<plague::SceneComponent>(this->_scene, 10);
                    startA.assign<plague::Transform>(pointA, 1.0f);  // position and scale
                    startA.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(255, 255, 28, 255), "A 3", 10, 1, cocos2d::Vec2(0, 20), 2.5f);
                    startA.assign<plague::AutoDestroyDescription>(3.0f);

                    entityx::Entity fireworks = es.create();
                    fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                    fireworks.assign<plague::Transform>(pointB, 1.0f);  // position and scale
                    fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(255, 25, 28, 255), "B 3", 10, 1, cocos2d::Vec2(0, 20), 2.5f);
                    fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                }, [&es, this](myBT::Context& context, double deltatime) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    if(transform->isDone()) {

                        entityx::Entity fireworks = es.create();
                        fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                        fireworks.assign<plague::Transform>(transform->get()->getPosition(), 1.0f);  // position and scale
                        fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(28, 255, 28, 255), "DONE 3", 10, 1, cocos2d::Vec2(0, 0), 2.5f);
                        fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                        return myBT::COMPLETED;
                    }
                    else
                        return myBT::RUNNING;
                }, [&es, this](myBT::Context& context) {

                    auto transform = context.stack.get<plague::Transform*>("transform");
                    entityx::Entity fireworks = es.create();
                    fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                    fireworks.assign<plague::Transform>(transform->get()->getPosition(), 1.0f);  // position and scale
                    fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(28, 255, 255, 255), "FIN 3", 10, 1, cocos2d::Vec2(0, -20), 2.5f);
                    fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                }
        };

        actions["go_to_column4"] = {
                [&es, this](myBT::Context& context) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    const float velocity = 200.0f;
                    cocos2d::Vec2 pointA = transform->get()->getPosition();
                    cocos2d::Vec2 pointB(level01::column4, pointA.y);
                    float start_time = pointA.distance(pointB) / velocity;
                    transform->runAction(cocos2d::MoveBy::create(start_time, pointB - pointA));

                    entityx::Entity startA = es.create();
                    startA.assign<plague::SceneComponent>(this->_scene, 10);
                    startA.assign<plague::Transform>(pointA, 1.0f);  // position and scale
                    startA.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(255, 255, 28, 255), "A 4", 10, 1, cocos2d::Vec2(0, 20), 2.5f);
                    startA.assign<plague::AutoDestroyDescription>(3.0f);

                    entityx::Entity fireworks = es.create();
                    fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                    fireworks.assign<plague::Transform>(pointB, 1.0f);  // position and scale
                    fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(255, 25, 28, 255), "B 4", 10, 1, cocos2d::Vec2(0, 20), 2.5f);
                    fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                }, [&es, this](myBT::Context& context, double deltatime) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    if(transform->isDone()) {

                        entityx::Entity fireworks = es.create();
                        fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                        fireworks.assign<plague::Transform>(transform->get()->getPosition(), 1.0f);  // position and scale
                        fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(28, 255, 28, 255), "DONE 4", 10, 1, cocos2d::Vec2(0, 0), 2.5f);
                        fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                        return myBT::COMPLETED;
                    }
                    else
                        return myBT::RUNNING;
                }, [&es, this](myBT::Context& context) {

                    auto transform = context.stack.get<plague::Transform*>("transform");
                    entityx::Entity fireworks = es.create();
                    fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                    fireworks.assign<plague::Transform>(transform->get()->getPosition(), 1.0f);  // position and scale
                    fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(28, 255, 255, 255), "FIN 4", 10, 1, cocos2d::Vec2(0, -20), 2.5f);
                    fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                }
        };

        actions["go_to_column5"] = {
                [&es, this](myBT::Context& context) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    const float velocity = 200.0f;
                    cocos2d::Vec2 pointA = transform->get()->getPosition();
                    cocos2d::Vec2 pointB(level01::column5, pointA.y);
                    float start_time = pointA.distance(pointB) / velocity;
                    transform->runAction(cocos2d::MoveBy::create(start_time, pointB - pointA));

                    entityx::Entity startA = es.create();
                    startA.assign<plague::SceneComponent>(this->_scene, 10);
                    startA.assign<plague::Transform>(pointA, 1.0f);  // position and scale
                    startA.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(255, 255, 28, 255), "A 5", 10, 1, cocos2d::Vec2(0, 20), 2.5f);
                    startA.assign<plague::AutoDestroyDescription>(3.0f);

                    entityx::Entity fireworks = es.create();
                    fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                    fireworks.assign<plague::Transform>(pointB, 1.0f);  // position and scale
                    fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(255, 25, 28, 255), "B 5", 10, 1, cocos2d::Vec2(0, 20), 2.5f);
                    fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                }, [&es, this](myBT::Context& context, double deltatime) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    if(transform->isDone()) {

                        entityx::Entity fireworks = es.create();
                        fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                        fireworks.assign<plague::Transform>(transform->get()->getPosition(), 1.0f);  // position and scale
                        fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(28, 255, 28, 255), "DONE 5", 10, 1, cocos2d::Vec2(0, 0), 2.5f);
                        fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                        return myBT::COMPLETED;
                    }
                    else
                        return myBT::RUNNING;
                }, [&es, this](myBT::Context& context) {

                    auto transform = context.stack.get<plague::Transform*>("transform");
                    entityx::Entity fireworks = es.create();
                    fireworks.assign<plague::SceneComponent>(this->_scene, 10);
                    fireworks.assign<plague::Transform>(transform->get()->getPosition(), 1.0f);  // position and scale
                    fireworks.assign<plague::LabelWithTTFUICompomnent>(cocos2d::Color4B(28, 255,  255, 255), "FIN 5", 10, 1, cocos2d::Vec2(0, -20), 2.5f);
                    fireworks.assign<plague::AutoDestroyDescription>(3.0f);

                }
        };

        actions["go_to_right"] = {
                [](myBT::Context& context) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    const float velocity = 110.0f;
                    cocos2d::Vec2 pointB(70, 70);
                    transform->runAction( cocos2d::EaseElasticOut::create( cocos2d::MoveBy::create(pointB.length() / velocity, pointB) ));
                }, [](myBT::Context& context, double deltatime) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    if(transform->isDone())
                        return myBT::COMPLETED;
                    else
                        return myBT::RUNNING;
                }, [](myBT::Context& context) {

                }
        };

        actions["go_to_left"] = {
                [](myBT::Context& context) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    const float velocity = 110.0f;
                    cocos2d::Vec2 pointB(-70, 70);
                    transform->runAction(cocos2d::EaseElasticOut::create(cocos2d::MoveBy::create(pointB.length() / velocity, pointB)));
                }, [](myBT::Context& context, double deltatime) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    if(transform->isDone())
                        return myBT::COMPLETED;
                    else
                        return myBT::RUNNING;
                }, [](myBT::Context& context) {

                }
        };

        conditions["can_go_left?"] = {
                [](myBT::Context& context, double deltatime) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    double myposition = transform->get()->getPosition().x;
                    return myposition > (level01::column1 + 50);
                }
        };

        conditions["can_go_right?"] = {
                [](myBT::Context& context, double deltatime) {
                    auto transform = context.stack.get<plague::Transform*>("transform");
                    double myposition = transform->get()->getPosition().x;
                    return myposition < (level01::column5 - 50);
                }
        };

        auto fullpath = cocos2d::FileUtils::getInstance()->getWritablePath() + "/" + brain_name + ".json";

        if(cocos2d::FileUtils::getInstance()->isFileExist(fullpath))
        {

            // READ behaviour
            bt.read_ai(fullpath, conditions, actions);

        }
        else
        {

            if(brain_name == "spider")
            {

                /*
                 * Acciones y condiciones parametrizadas ?
                 * Umbrales parametrizados
                 * Lista de opciones
                 */

                auto seq_00 = bt.make_node<myBT::Sequence>("main_control");

                    auto selector_00 = seq_00->make_node<myBT::Selector>("decision A")->setRandom(true);

                        selector_00->make_node<myBT::Action>("go_to_column1", actions.at("go_to_column1"));
                        selector_00->make_node<myBT::Action>("go_to_column2", actions.at("go_to_column2"));
                        selector_00->make_node<myBT::Action>("go_to_column3", actions.at("go_to_column3"));
                        selector_00->make_node<myBT::Action>("go_to_column4", actions.at("go_to_column4"));
                        selector_00->make_node<myBT::Action>("go_to_column5", actions.at("go_to_column5"));

                    auto selector_01 = seq_00->make_node<myBT::Selector>("decision B")->setRandom(true)->setAutoReset(true);

                        auto seq_02 = selector_01->make_node<myBT::Sequence>("sequence_izq");

                            seq_02->make_node<myBT::Condition>("can_go_left?", conditions.at("can_go_left?"));
                            seq_02->make_node<myBT::Action>("go_to_left", actions.at("go_to_left"));
                            seq_02->make_node<myBT::Action>("go_to_right", actions.at("go_to_right"));

                        auto seq_03 = selector_01->make_node<myBT::Sequence>("sequence_der");

                            seq_03->make_node<myBT::Condition>("can_go_right?", conditions.at("can_go_right?"));
                            seq_03->make_node<myBT::Action>("go_to_right", actions.at("go_to_right"));
                            seq_03->make_node<myBT::Action>("go_to_left", actions.at("go_to_left"));

                        auto seq_04 = selector_01->make_node<myBT::Sequence>("sequence_else");

                            seq_04->make_node<myBT::Action>("go_to_right", actions.at("go_to_right"));
                            seq_04->make_node<myBT::Action>("go_to_left", actions.at("go_to_left"));
            }
            else
            {
                // unknown IA
                std::abort();
            }

            bt.write_ai(fullpath, conditions, actions);
        }
    }

    void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		es.each<BrainComponent, Transform, EnemyCountSensorComponent, CharacterComponent>([&](entityx::Entity entity, BrainComponent& brain, Transform& transform, EnemyCountSensorComponent& count_sensor, CharacterComponent& character) {

		    if(transform.configured) {

                myBT::Parallel &bt = trees[brain.name];
                myBT::ConditionRepository &conditions = condition_map[brain.name];
                myBT::ActionRepository &actions = action_map[brain.name];

                brain.update_fw(&bt, conditions, actions, es, events, dt, transform, count_sensor, character);
            }

		});
		es.each<SpiderBrainComponent, Transform, ProjectilCountSensorComponent>([&](entityx::Entity entity, SpiderBrainComponent& brain, Transform& transform, ProjectilCountSensorComponent& count_sensor) {

            if(transform.configured) {

                myBT::Parallel &bt = trees[brain.name];
                myBT::ConditionRepository &conditions = condition_map[brain.name];
                myBT::ActionRepository &actions = action_map[brain.name];

                brain.update_fw(&bt, conditions, actions, es, events, dt, transform, count_sensor);
            }

        });
    }

protected:
    std::unordered_map<std::string, myBT::Parallel > trees;
    std::unordered_map<std::string, myBT::ConditionRepository > condition_map;
    std::unordered_map<std::string, myBT::ActionRepository > action_map;
    cocos2d::Scene* _scene;
};

}

#endif
