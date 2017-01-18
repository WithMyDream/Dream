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
{
    
}

GameScene::~GameScene()
{
    
}

bool GameScene::init()
{
    REGISTER_EVENT(EventCreateUnit, onCreateUnit);
    
    scheduleUpdate();
    
    return true;
}

void GameScene::onCreateUnit(EventParams &params)
{
    ECreateUnit create = static_cast<ECreateUnit&>(params);
    CCLOG("[onCreateUnit] %08x ", create._unit);
    Actor* actor = Actor::create();
    actor->setUnit(create._unit);
    addChild(actor);
    _actors.push_back(actor);
}

void GameScene::update(float dt)
{
    std::vector<Actor*>::iterator it = _actors.begin();
    for ( ; it != _actors.end(); ++it)
        (*it)->update(dt);
}
