// System/Receiver class AnimationSystem
//
// Ricardo Marmolejo García 2019
//
// use: 
//
#pragma once
#ifndef _AnimationSystem_H_
#define _AnimationSystem_H_

#include <cocos2d.h>
#include "entityx/entityx.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "FireCommand.h"

namespace plague {

struct AnimationSystem : public entityx::System<AnimationSystem>, public entityx::Receiver<AnimationSystem>
{
	explicit AnimationSystem()
	{
		
	}

	virtual ~AnimationSystem()
	{
		
	}

	void configure(entityx::EntityManager& es, entityx::EventManager& events) override
	{
		events.subscribe<plague::LeftCommand>(*this);
		events.subscribe<plague::RightCommand>(*this);
		events.subscribe<plague::FireCommand>(*this);
	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
	{
		// aplicar movimiento en funcion de la animacion activa	
	}

	void receive(const plague::LeftCommand& event)
	{
		// cambiar la animacion
	}

	void receive(const plague::RightCommand& event)
	{
		// cambiar la animacion
	}

	void receive(const plague::FireCommand& event)
	{
		// cambiar la animacion
	}
};

}

#endif
