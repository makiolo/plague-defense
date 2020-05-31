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
	explicit SceneComponent(cocos2d::Scene* scene_, int zorder_ = 0)
		: scene(scene_)
		, zorder(zorder_)
	{
		
	}

	cocos2d::Scene* get() const
	{
		return scene;
	}

	cocos2d::Scene* scene;
	int zorder;
};

}

#endif /* SCENECOMPONENT_H_ */

