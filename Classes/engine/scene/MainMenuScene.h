#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include <cocos2d.h>
#include "entityx/entityx.h"

namespace plague {

class MainMenuScene : public cocos2d::Scene
{
public:
	MainMenuScene();
	virtual ~MainMenuScene();

	static cocos2d::Scene* createScene();

	virtual bool init() override;
	virtual void render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection) final;

	CREATE_FUNC(MainMenuScene);
protected:
	entityx::EntityX ex;
};

}

#endif // __MAINMENU_SCENE_H__
