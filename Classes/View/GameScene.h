#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
using namespace cocos2d;

class GameScene : public Scene
{
public:
    static GameScene* create();
    
    GameScene();
    ~GameScene();
    bool init();
    
    void update(float dt);
    
private:
    
    
private:
    
};

#endif // __GameScene_H__
