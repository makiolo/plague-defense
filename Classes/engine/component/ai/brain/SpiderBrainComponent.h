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

namespace plague {

struct SpiderBrainComponent : public entityx::Component<SpiderBrainComponent>
{
	explicit SpiderBrainComponent(entityx::Entity::Id id, const std::string& name)
		: whoami(id)
		, bt(name)
		, is_configured(false)
	{
		
	}

	~SpiderBrainComponent()
	{
		bt.free_childs();
	}

	void configure_fw(entityx::EntityManager& es, entityx::EventManager& events, plague::Transform& transform)
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

		actions["go_to_spawn"] = {
			[&]() {
				const float velocity = 300.0f;
				cocos2d::Vec2 pointA = transform.get()->getPosition();
				cocos2d::Vec2 pointB(level01::column1, pointA.y);
				float start_time = pointA.distance(pointB) / velocity;
				transform.get()->runAction(cocos2d::MoveBy::create(start_time, pointB - pointA));
			}, [&](double deltatime) {
				cocos2d::Vec2 pointA = transform.get()->getPosition();
				cocos2d::Vec2 pointB(level01::column1, pointA.y);
				if(pointA.distanceSquared(pointB) > (1.0f*1.0f))
					return myBT::RUNNING;
				else
					return myBT::COMPLETED;
			}, [&](bool interrupted) {
				transform.get()->cleanup();
			}
		};

		actions["go_to_roof"] = {
			[&]() {
				const float velocity = 300.0f;
				cocos2d::Vec2 pointA = transform.get()->getPosition();
				cocos2d::Vec2 pointB(level01::column3, level01::ceil);
				float start_time = pointA.distance(pointB) / velocity;
				transform.get()->runAction(cocos2d::MoveBy::create(start_time, pointB - pointA));
			}, [&](double deltatime) {
				cocos2d::Vec2 pointA = transform.get()->getPosition();
				cocos2d::Vec2 pointB(level01::column3, level01::ceil);
				if (pointA.distanceSquared(pointB) > (1.0f * 1.0f))
					return myBT::RUNNING;
				else
					return myBT::COMPLETED;
			}, [&](bool interrupted) {
				transform.get()->cleanup();
			}
		};

		auto sequence_00 = bt.make_node<myBT::Sequence>("main_control");
		sequence_00->make_node<myBT::Action>("go_to_spawn", actions["go_to_spawn"]);
		sequence_00->make_node<myBT::Action>("go_to_roof", actions["go_to_roof"]);

#ifdef __ANDROID__
		/*
        // https://discuss.cocos2d-x.org/t/please-help-cocos2d-x-to-determine-whats-the-correct-path-to-save-a-file-on-ios-and-android/5578/19
        Persistant data like savegames, highscores, replays
        Android: Contect.getFilesDir()
        iOS: /Documents (Note it is NOT /Library/Documents)

        Temporary data like user avatars:
        Android: Context.getCacheDir()
        iOS: /Library/Caches
        */
		auto fullpath = cocos2d::FileUtils::getInstance()->getWritablePath() + "/spider.json";
		bt.write_ai(fullpath, conditions, actions);
#endif

		bt.configure(context, bt.get_name());

		is_configured = true;
	}

	void update_fw(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt, plague::Transform& transform)
	{
		if (!is_configured)
			configure_fw(es, events, transform);

		bt.update(context, bt.get_name(), dt);
	}

	entityx::Entity::Id whoami;
	myBT::Context context;
	myBT::Parallel bt;
	myBT::ActionRepository actions;
	myBT::ConditionRepository conditions;
	bool is_configured;
};

}

#endif
