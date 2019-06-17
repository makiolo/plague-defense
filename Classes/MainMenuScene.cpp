#include "MainMenuScene.h"
//
#include "entityx/entityx.h"
// SCENES
#include "Level01.h"

USING_NS_CC;

namespace plague {

Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	/////////////////////////////////////////////////////////////

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////////////////////////////////////

	auto playButton = MenuItemImage::create(
		"img/menu/play.png",
		"img/menu/play_hover.png",
		CC_CALLBACK_1(MainMenuScene::menuPlayCallback, this));

	if (playButton == nullptr ||
		playButton->getContentSize().width <= 0 ||
		playButton->getContentSize().height <= 0)
	{
		// throw std::exception("Error loading play button.");
	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + visibleSize.height / 2;
		playButton->setPosition(Vec2(x, y));
	}

	auto menu = Menu::create(playButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	return true;
}

void MainMenuScene::menuPlayCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(2, Level01::create()));
	// Director::getInstance()->replaceScene(Level01::create());
}

}
