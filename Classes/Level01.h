#ifndef __LEVEL01_SCENE_H__
#define __LEVEL01_SCENE_H__

#include "cocos2d.h"
#include "entityx/entityx.h"

class Level01 : public cocos2d::Scene
{
public:
    Level01();
    virtual ~Level01();

    static cocos2d::Scene* createScene();

    virtual bool init() override;
	void render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection = nullptr) override;    
    
    CREATE_FUNC(Level01);
protected:
	entityx::EntityX ex;
};

#endif // __LEVEL01_SCENE_H__
