/* Component class SpiderBrainComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _SpiderBrainComponent_H_
#define _SpiderBrainComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "myBT/myBT.h"
#include "engine/component/Transform.h"
#include "engine/scene/constants/Level01Constants.h"
#include "engine/event/ConsoleInfoEvent.h"

namespace plague {

struct SpiderBrainComponent : public entityx::Component<SpiderBrainComponent>
{
	explicit SpiderBrainComponent(const std::string& name)
		: bt(name)
		, is_configured(false)
	{
		
	}

	~SpiderBrainComponent()
	{
		bt.free_childs();
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform, ProjectilCountSensorComponent& count_sensor)
	{
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
			[&]() {
				const float velocity = 300.0f;
				cocos2d::Vec2 pointA = transform.get()->getPosition();
				cocos2d::Vec2 pointB(level01::column1, pointA.y);
				float start_time = pointA.distance(pointB) / velocity;
				transform.runAction(cocos2d::MoveTo::create(start_time, pointB));
			}, [&](double deltatime) {
				if(transform.isDone())
                    return myBT::COMPLETED;
				else
                    return myBT::RUNNING;
			}, [&]() {

			}
		};

        actions["go_to_column2"] = {
                [&]() {
                    const float velocity = 300.0f;
                    cocos2d::Vec2 pointA = transform.get()->getPosition();
                    cocos2d::Vec2 pointB(level01::column2, pointA.y);
                    float start_time = pointA.distance(pointB) / velocity;
                    transform.runAction(cocos2d::MoveTo::create(start_time, pointB));
                }, [&](double deltatime) {
                    if(transform.isDone())
                        return myBT::COMPLETED;
                    else
                        return myBT::RUNNING;
                }, [&]() {

                }
        };

        actions["go_to_column3"] = {
                [&]() {
                    const float velocity = 300.0f;
                    cocos2d::Vec2 pointA = transform.get()->getPosition();
                    cocos2d::Vec2 pointB(level01::column3, pointA.y);
                    float start_time = pointA.distance(pointB) / velocity;
                    transform.runAction(cocos2d::MoveTo::create(start_time, pointB));
                }, [&](double deltatime) {
                    if(transform.isDone())
                        return myBT::COMPLETED;
                    else
                        return myBT::RUNNING;
                }, [&]() {

                }
        };

        actions["go_to_column4"] = {
                [&]() {
                    const float velocity = 300.0f;
                    cocos2d::Vec2 pointA = transform.get()->getPosition();
                    cocos2d::Vec2 pointB(level01::column4, pointA.y);
                    float start_time = pointA.distance(pointB) / velocity;
                    transform.runAction(cocos2d::MoveTo::create(start_time, pointB));
                }, [&](double deltatime) {
                    if(transform.isDone())
                        return myBT::COMPLETED;
                    else
                        return myBT::RUNNING;
                }, [&]() {

                }
        };

        actions["go_to_column5"] = {
                [&]() {
                    const float velocity = 300.0f;
                    cocos2d::Vec2 pointA = transform.get()->getPosition();
                    cocos2d::Vec2 pointB(level01::column5, pointA.y);
                    float start_time = pointA.distance(pointB) / velocity;
                    transform.runAction(cocos2d::MoveTo::create(start_time, pointB));
                }, [&](double deltatime) {
                    if(transform.isDone())
                        return myBT::COMPLETED;
                    else
                        return myBT::RUNNING;
                }, [&]() {

                }
        };

        actions["go_to_right"] = {
                [&]() {
                    const float velocity = 110.0f;
                    cocos2d::Vec2 pointB(70, 70);
                    transform.runAction( cocos2d::EaseElasticOut::create( cocos2d::MoveBy::create(pointB.length() / velocity, pointB) ));
                }, [&](double deltatime) {
                    if(transform.isDone())
                        return myBT::COMPLETED;
                    else
                        return myBT::RUNNING;
                }, [&]() {

                }
        };

        actions["go_to_left"] = {
                [&]() {
                    const float velocity = 110.0f;
                    cocos2d::Vec2 pointB(-70, 70);
                    transform.runAction(cocos2d::EaseElasticOut::create(cocos2d::MoveBy::create(pointB.length() / velocity, pointB)));
                }, [&](double deltatime) {
                    if(transform.isDone())
                        return myBT::COMPLETED;
                    else
                        return myBT::RUNNING;
                }, [&]() {

                }
        };

        conditions["can_go_left?"] = {
                [&](double deltatime) {
                    double myposition = transform.get()->getPosition().x;
                    return myposition > (level01::column1 + 50);
                }
        };

        conditions["can_go_right?"] = {
                [&](double deltatime) {
                    double myposition = transform.get()->getPosition().x;
                    return myposition < (level01::column5 - 50);
                }
        };

        conditions["can_go_right? 2222"] = {
                [&](double deltatime) {
                    double myposition = transform.get()->getPosition().x;
                    return myposition < (level01::column5 - 50);
                }
        };


        auto fullpath = cocos2d::FileUtils::getInstance()->getWritablePath() + "/" + bt.get_name() + ".json";

        if(cocos2d::FileUtils::getInstance()->isFileExist(fullpath)) {

            // READ behaviour
            bt.read_ai(fullpath, conditions, actions);

        }
        else {

            auto name = bt.get_name();

            if(name == "spider") {

                auto seq_00 = bt.make_node<myBT::Sequence>("main_control");

                auto selector_00 = seq_00->make_node<myBT::Selector>("selector_00")->setRandom(true);

                selector_00->make_node<myBT::Action>("go_to_column1", actions["go_to_column1"]);
                selector_00->make_node<myBT::Action>("go_to_column2", actions["go_to_column2"]);
                selector_00->make_node<myBT::Action>("go_to_column3", actions["go_to_column3"]);
                selector_00->make_node<myBT::Action>("go_to_column4", actions["go_to_column4"]);
                selector_00->make_node<myBT::Action>("go_to_column5", actions["go_to_column5"]);

                auto for_00 = seq_00->make_node<myBT::For>("for_00");

                auto seq_01 = for_00->make_node<myBT::Sequence>("seq_01");

                auto selector_01 = seq_01->make_node<myBT::Selector>("selector_01")->setRandom(true);

                auto seq_02 = selector_01->make_node<myBT::Sequence>("seq_02");

                seq_02->make_node<myBT::Condition>("can_go_left?", conditions["can_go_left?"]);
                seq_02->make_node<myBT::Action>("go_to_left", actions["go_to_left"]);
                seq_02->make_node<myBT::Action>("go_to_right", actions["go_to_right"]);

                auto seq_03 = selector_01->make_node<myBT::Sequence>("seq_03");

                seq_03->make_node<myBT::Condition>("can_go_right?", conditions["can_go_right?"]);
                seq_03->make_node<myBT::Action>("go_to_right", actions["go_to_right"]);
                seq_03->make_node<myBT::Action>("go_to_left", actions["go_to_left"]);
            }
            else
            {
                // unknown IA
                std::abort();
            }

            bt.write_ai(fullpath, conditions, actions);
        }

        bt.configure(context, bt.get_name());

        is_configured = true;
	}

	void update_fw(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt, plague::Transform& transform, plague::ProjectilCountSensorComponent& count_sensor)
	{
		if (!is_configured)
			configure_fw(es, events, transform, count_sensor);

		bt.clearTraces(context);
		bt.update(context, bt.get_name(), dt);
        for(auto flow : context)
        {
            std::stringstream ss;
            ss << "\"" << flow.first << "\": " << flow.second.traces.back();
            events.emit<plague::ConsoleInfoEvent>(bt.get_name(), ss.str());
        }
	}

	// Contexto individual
	myBT::Context context;
	// Arbol compartido
	myBT::Parallel bt;
	myBT::ActionRepository actions;
	myBT::ConditionRepository conditions;
	bool is_configured;
};

}

#endif
