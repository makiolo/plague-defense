// Component class CombatPointsComponent
//
//
// Created by Ricardo Marmolejo García on 6/9/2020.
//
//
// use: 
//
#pragma once
#ifndef _CombatPointsComponent_H_
#define _CombatPointsComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct CombatPointsComponent : public entityx::Component<CombatPointsComponent>
{
	explicit CombatPointsComponent(double life_ = 100.0f, double attack_ = 1.0f, double defense_ = 1.0f)
	    : life(life_)
	    , attack(attack_)
	    , defense(defense_)
	{
		;
	}

	~CombatPointsComponent()
    {

    }

	void on_hit(const CombatPointsComponent& other)
    {
	    this->life -= (this->get_attack() - other.get_defense());
    }

    double get_attack() const
    {
	    // apply modificators of attack
	    return attack;
	}

    double get_defense() const
    {
	    // apply modificators of defense
        return defense;
    }

	double life;
	double attack;
	double defense;
};

}

#endif //_CombatPointsComponent_H_