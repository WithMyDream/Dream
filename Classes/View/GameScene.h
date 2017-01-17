#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "Actor.h"
#include "../Logic/EventMgr.h"
#include <vector>

using namespace cocos2d;

class GameScene : public Scene
{
public:
    static GameScene* create();
    
    GameScene();
    ~GameScene();
    bool init();
    
    void onCreateUnit(EventParams &params);
    
    void update(float dt);
    
private:
    
    
private:
    std::vector<Actor*> _actors;
};

#endif // __GameScene_H__
