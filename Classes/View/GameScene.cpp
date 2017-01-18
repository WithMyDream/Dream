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
    Scene::init();
    
    REGISTER_EVENT(EventCreateUnit, onCreateUnit);
    
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
    CCLOG("[onCreateUnit] %08x ", create._unit);
    Actor* actor = Actor::create();
    actor->setUnit(create._unit);
    actor->setLocalZOrder(-1);
    addChild(actor);
    _actors.push_back(actor);
}

void GameScene::update(float dt)
{
    std::vector<Actor*>::iterator it = _actors.begin();
    for ( ; it != _actors.end(); ++it)
        (*it)->update(dt);
}
