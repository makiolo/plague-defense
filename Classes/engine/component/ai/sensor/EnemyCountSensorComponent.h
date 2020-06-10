/*
 * Componente (Sensor) que contiene los contadores principales de su entorno
 */
/* Component class EnemyCountSensorComponent
*
*  Ricardo Marmolejo García 2019
*/
#pragma once
#ifndef _CountSensorComponent_H_
#define _CountSensorComponent_H_

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct EnemyCountSensorComponent : public entityx::Component<EnemyCountSensorComponent>
{
	explicit EnemyCountSensorComponent()
		: x(0)
	{
		
	}

	// posicion x con mayor numero de enemigos
	double x;
};

}

#endif
