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
    
    
    return true;
}

void GameScene::update(float dt)
{
    
}
