#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

namespace entityx {
	class EntityX;
}

class Level01 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection = nullptr) override;    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(Level01);
protected:
	std::unique_ptr<entityx::EntityX> ex;
};

#endif // __HELLOWORLD_SCENE_H__
