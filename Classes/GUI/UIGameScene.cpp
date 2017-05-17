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
    Size winSize = cocos2d::Director::getInstance()->getWinSize();
    _world->setMainUnitViewSize(b2Vec2(winSize.width/B2SCALE, winSize.height/B2SCALE));
    
    // main unit
    Unit* mainUnit = _world->createUnit(1);
    
    mainUnit->getB2Body()->SetTransform(b2Vec2(_world->getMainUnitViewSize().x/2.0f, _world->getMainUnitViewSize().y/2.0f), mainUnit->getB2Body()->GetAngle());
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.8f;
    fixtureDef.restitution = 0.0f;
    b2CircleShape circleShape;
    circleShape.m_radius = 50.0f/B2SCALE;
    fixtureDef.shape = &circleShape;
    mainUnit->getB2Body()->CreateFixture(&fixtureDef);
    
    std::string name("Jon");
	mainUnit->setName(name);
	mainUnit->setType(UnitTypeHero);
    b2Vec2 pos((mainUnit->getPostion().x + 200.0f/B2SCALE), mainUnit->getPostion().y + 100.0f/B2SCALE);
    mainUnit->setPosition(pos);
    _world->setMainUnit(mainUnit);
    
    
    // test rope
    //Rope* rope = Rope::create(_world, 1);
    
    //rope->jointFirstTo(_world->joint1);
    //rope->jointLastTo(_world->getMainUnit());
    
    //rope->linkUnits(_world->joint1, _world->getMainUnit());
    
    mainUnit->hang(_world->joint1);
    
    
    return true;
}


