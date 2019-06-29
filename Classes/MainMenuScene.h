#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include <cocos2d.h>

namespace plague {

class MainMenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void menuPlayCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(MainMenuScene);
};

}

#endif // __MAINMENU_SCENE_H__
