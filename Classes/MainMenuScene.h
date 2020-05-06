#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include <cocos2d.h>

namespace plague {

class MainMenuScene : public cocos2d::Scene
{
public:
	MainMenuScene();
	virtual ~MainMenuScene();

	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(MainMenuScene);
};

}

#endif // __MAINMENU_SCENE_H__
