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
    Unit* mainUnit = _world->createUnit(1);
	mainUnit->setName(std::string("Jon"));
	mainUnit->setType(UnitTypeHero);
    b2Vec2 pos((mainUnit->getPostion().x + 200.0f/B2SCALE), mainUnit->getPostion().y + 100.0f/B2SCALE);
    mainUnit->setPosition(pos);
    _world->setMainUnit(mainUnit);
    Size winSize = cocos2d::Director::getInstance()->getWinSize();
    _world->setMainUnitViewSize(b2Vec2(winSize.width/B2SCALE, winSize.height/B2SCALE));
    
    // test rope
    Rope* rope = Rope::create(_world, 1);
    rope->linkUnits(_world->joint1, _world->getMainUnit());
    //rope->jointFirstTo(_world->joint1);
    //rope->jointLastTo(_world->getMainUnit());
    
    
    return true;
}


