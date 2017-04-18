#include "UIGameScene.h"

UIGameScene::UIGameScene()
: _joystick(nullptr)
{
    
}

UIGameScene::~UIGameScene()
{
    CC_SAFE_DELETE(_world);
}

bool UIGameScene::init()
{
    Scene::init();
    
    EventMgr::getInatence();
    _world = World::create();
    _world->retain();
    _scene = GameScene::create();
    _scene->setDebugDraw(_world->getB2World());
    addChild(_scene);
    
    _joystick = UIInputLayer::create();
    addChild(_joystick);
    
    // test
    _world->loadWorldTMX("Map/map001.tmx");
    _world->setMainUnit(_world->createUnit(1));
    
    // test rope
    Rope* rope = Rope::create(_world, 1);
    rope->jointFirstTo(_world->joint1);
    rope->jointLastTo(_world->getMainUnit());
    
    
    return true;
}


