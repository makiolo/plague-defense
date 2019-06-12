#pragma once
#ifndef _CHANGESCENE_H_
#define _CHANGESCENE_H_

#include <cocos2d.h>

namespace plague {

struct ChangeScene {
	explicit ChangeScene(cocos2d::Scene* scene_)
		: scene(scene_)
	{
		
	}

	cocos2d::Scene* scene;
};

}

#endif
