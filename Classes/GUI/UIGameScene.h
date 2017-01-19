#ifndef __UIGameScene_H__
#define __UIGameScene_H__

#include "cocos2d.h"
#include "UIInputLayer.h"

using namespace cocos2d;

class UIGameScene : public Scene
{
public:
    CREATE_FUNC(UIGameScene);
    
    UIGameScene();
    ~UIGameScene();
    bool init() override;
    
private:
    UIInputLayer* _joystick;
};

#endif // __UIGameScene_H__
