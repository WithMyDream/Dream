#include "GameScene.h"

GameScene* GameScene::create()
{
    GameScene* gameScene = new GameScene();
    if (gameScene && gameScene->init()) {
        gameScene->autorelease();
    }
    return gameScene;
}

GameScene::GameScene()
: _debugDrawLayer(nullptr)
{
    
}

GameScene::~GameScene()
{
    
}

bool GameScene::init()
{
    Node::init();
    
    REGISTER_EVENT(EventCreateUnit, onCreateUnit);
    REGISTER_EVENT(EventJoystick, onJoystick);
    
    scheduleUpdate();
    
    return true;
}

void GameScene::setDebugDraw(b2World* b2word)
{
    _debugDrawLayer = B2DebugDrawLayer::create(b2word, B2SCALE);
    addChild(_debugDrawLayer, 9999999);
}

void GameScene::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
   if (_debugDrawLayer)
       _debugDrawLayer->draw(renderer, transform, flags);
}

void GameScene::onCreateUnit(EventParams &params)
{
    ECreateUnit create = static_cast<ECreateUnit&>(params);
    //CCLOG("[onCreateUnit] %08x ", create._unit);
    Actor* actor = Actor::create();
    actor->setUnit(create._unit);
    actor->setLocalZOrder(-1);
    addChild(actor);
    _actors.push_back(actor);
    
    runAction(Follow::create(actor));
}

void GameScene::onJoystick(EventParams &params)
{
    EJoystick joystick = static_cast<EJoystick&>(params);
    //CCLOG("angle %f", joystick._angle);
    if (joystick._angle == -1) {
        return;
    }
    float r = CC_DEGREES_TO_RADIANS(joystick._angle);
    setPosition(getPositionX() + 10*cosf(r), getPositionY() + 10*sinf(r));
}

void GameScene::update(float dt)
{
    std::vector<Actor*>::iterator it = _actors.begin();
    for ( ; it != _actors.end(); ++it)
        (*it)->update(dt);
}
