#ifndef __LEVEL01_SCENE_H__
#define __LEVEL01_SCENE_H__

#include "cocos2d.h"
// #include <network/WebSocket.h>
#include "entityx/entityx.h"

class Level01 : public cocos2d::Scene  // , public cocos2d::network::WebSocket::Delegate
{
public:
    Level01();
    virtual ~Level01();

    static cocos2d::Scene* createScene();

    virtual bool init() override;
	void render(cocos2d::Renderer* renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection = nullptr) override;    

	/*
    virtual void onOpen(cocos2d::network::WebSocket* ws);// override;
    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);// override;
    virtual void onClose(cocos2d::network::WebSocket* ws);// override;
    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);// override;
    */

    CREATE_FUNC(Level01);
protected:
    // cocos2d::network::WebSocket* websocket;
	entityx::EntityX ex;
};

#endif // __LEVEL01_SCENE_H__
