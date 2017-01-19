#include "UIGameScene.h"

#include "../Logic/World.h"
#include "../Logic/EventMgr.h"
#include "../View/GameScene.h"

UIGameScene::UIGameScene()
: _joystick(nullptr)
{
    
}

UIGameScene::~UIGameScene()
{
    
}

bool UIGameScene::init()
{
    Scene::init();
    
    EventMgr::getInatence();
    World* world = World::create();
    world->retain();
    GameScene* scene = GameScene::create();
    scene->setDebugDraw(world->getB2World());
    addChild(scene);
    
    _joystick = UIInputLayer::create();
    addChild(_joystick);
    
    // test
    world->createUnit(1);
    
    return true;
}


