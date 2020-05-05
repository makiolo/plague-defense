/*
 * SceneComponent.h
 *
 *  Created on: May 5, 2020
 *      Author: ricardomg
 */

#ifndef SCENECOMPONENT_H_
#define SCENECOMPONENT_H_


#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

struct SceneComponent : public entityx::Component<SceneComponent>
{
	explicit SceneComponent(cocos2d::Scene* scene_)
		: scene(scene_)
	{
		
	}

	cocos2d::Scene* get() const
	{
		return scene;
	}

	// need scene, but i dont owner
	cocos2d::Scene* scene;
};

}

#endif /* SCENECOMPONENT_H_ */

