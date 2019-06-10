/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
//
#include <random>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);

	// cielo
	auto bg = cocos2d::LayerColor::create(Color4B(185, 220, 234, 255));
	this->addChild(bg, 0);


	// nube
	// 
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> scale_random{ 0.2, 0.4 };
	std::normal_distribution<> height_random{ 150, 100 };
	std::uniform_int_distribution<> width_random{ 150, 300 };

	for(int i=0; i<10; ++i)
	{
		auto cloud = Sprite::create("img/decoration/cloud.png");
		if (cloud == nullptr)
		{
			problemLoading("'img/decoration/cloud.png'");
		}
		else
		{
			// position the sprite on the center of the screen
			float scale = scale_random(gen);
			Vec2 position((width_random(gen)*(1+i)) % int(visibleSize.width), height_random(gen));
			cloud->setPosition(Vec2(position.x + (scale * cloud->boundingBox().size.width / 2), visibleSize.height - position.y - scale * (cloud->boundingBox().size.height / 2)));
			cloud->setScale(scale);

			// add the sprite as a child to this layer
			this->addChild(cloud, 1);
			_clouds.push_back(cloud);
		}
	}

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

	/*
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 2);
    }
	*/

    // add "HelloWorld" splash screen"

    auto sprite = Sprite::create("img/building/house.png");
    if (sprite == nullptr)
    {
        problemLoading("'img/building/house.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, 310));
		sprite->setScale(1.7f);

        // add the sprite as a child to this layer
        this->addChild(sprite, 2);
    }

    return true;
}


void HelloWorld::render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection)
{
	cocos2d::Scene::render(renderer, eyeTransform, eyeProjection);
	auto visibleSize = Director::getInstance()->getVisibleSize();

	for (auto cloud : _clouds)
	{
		float width_cloud = cloud->getScale() * cloud->boundingBox().size.width;
		if (cloud->getPosition().x > (visibleSize.width + width_cloud))
		{
			Vec2 position = cloud->getPosition();
			position.x -= (visibleSize.width + width_cloud);
			cloud->setPosition(position);
		}
		else
		{
			cloud->setPosition(cloud->getPosition() + Vec2(1.0f / (60.0f * cloud->getScaleX()), 0));
		}
	}
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
