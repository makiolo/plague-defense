#pragma once
#ifndef _CLOUD_H_
#define _CLOUD_H_

#include <cocos2d.h>

namespace plague {

struct Sprite {
	explicit Sprite(cocos2d::Sprite* sprite_)
		: sprite(sprite_)
	{
		sprite->retain();
	}

	~Sprite()
	{
		sprite->removeFromParent();
		sprite->release();
	}

	cocos2d::Sprite* sprite;
};

}

#endif