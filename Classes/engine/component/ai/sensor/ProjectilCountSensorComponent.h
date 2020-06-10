// Component class ProjectilCountSensorComponent
//
//
// Created by Ricardo Marmolejo García on 6/4/2020.
//
//
// use: 
//
#pragma once
#ifndef _ProjectilCountSensorComponent_H_
#define _ProjectilCountSensorComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct ProjectilCountSensorComponent : public entityx::Component<ProjectilCountSensorComponent>
{
	explicit ProjectilCountSensorComponent()
	    : x(0)
	{
		
	}

	// posicion x con más proyectiles
	double x;
};

}

#endif //_ProjectilCountSensorComponent_H_