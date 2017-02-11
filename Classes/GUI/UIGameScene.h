#ifndef __UIGameScene_H__
#define __UIGameScene_H__

#include "cocos2d.h"
#include "UIInputLayer.h"

#include "../Logic/World.h"
#include "../Logic/EventMgr.h"
#include "../View/GameScene.h"

using namespace cocos2d;

class UIGameScene : public Scene
{
public:
    CREATE_FUNC(UIGameScene);
    
    UIGameScene();
    ~UIGameScene();
    bool init() override;
    
private:
    World*          _world;
    GameScene*      _scene;
    
    UIInputLayer*   _joystick;
};

#endif // __UIGameScene_H__
