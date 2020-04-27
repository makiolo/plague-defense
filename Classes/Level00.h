#pragma once

#include "cocos2d.h"

class Level00 : public cocos2d::Scene
{
public:
	Level00();
	virtual ~Level00();

    static cocos2d::Scene* createScene();

    virtual bool init();
    void render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection = nullptr) override;

    CREATE_FUNC(Level00);
};

