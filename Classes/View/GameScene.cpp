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
	_actors.reserve(64);
	_deleteActorIndexs.reserve(64);
}

GameScene::~GameScene()
{
    
}

bool GameScene::init()
{
    Node::init();
    
    REGISTER_EVENT(EventCreateUnit, onCreateUnit);
    REGISTER_EVENT(EventDestroyUnit, onDestroyUnit);
	REGISTER_EVENT(EventSetMainUnit, onSetMainUnit);
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
    Actor* actor = Actor::create(create._unit);
    actor->setLocalZOrder(-1);
    addChild(actor);
    _actors.push_back(actor);
    
	if (actor->getUnit()->getID() == -1)
		actor->setVisible(false);
}

void GameScene::onCreateRope(EventParams &params)
{
	ECreateRope create = static_cast<ECreateRope&>(params);
	//CCLOG("[onCreateRope] %08x ", create._rope);
	Actor* actor = Actor::create(create._rope);
	actor->setLocalZOrder(-1);
	addChild(actor);
	_actors.push_back(actor);

	if (actor->getUnit()->getID() == -1)
		actor->setVisible(false);
}

void GameScene::onDestroyUnit(EventParams &params)
{
	EDestroyUnit create = static_cast<EDestroyUnit&>(params);

	Actor* actor = findActorWithUnit(create._unit);
	if (actor)
		actor->destroy();
}

void GameScene::onSetMainUnit(EventParams &params)
{
	ESetMainUnit create = static_cast<ESetMainUnit&>(params);

	Actor* actor = findActorWithUnit(create._unit);
	if (actor)
	{
		actor->addChild(Sprite::create("HelloWorld.png")); // test
		runAction(Follow::create(actor));
	}
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

Actor* GameScene::findActorWithUnit(Unit* unit)
{
	int num = _actors.size();
	for (int i = 0; i < num; ++i)
	{
		Actor* actor = _actors[i];
		if (actor->getUnit() == unit)
			return actor;
	}
	return nullptr;
}

void GameScene::update(float dt)
{
	// update units
	_deleteActorIndexs.clear();
	int num = _actors.size();
	for (int i = 0; i < num; ++i)
	{
		Actor* actor = _actors[i];
		actor->update(dt);
		if (actor->isDestroy())
		{
			_deleteActorIndexs.push_back(i);
		}
	}

	// handle delete
	int deleteNum = _deleteActorIndexs.size();
	for (int i = 0; i < deleteNum; ++i)
	{
		int deleteIndex = _deleteActorIndexs[i];
		int backIndex = num - 1 - i;
		Actor* tempActor = _actors[backIndex];
		_actors[backIndex] = _actors[deleteIndex];
		_actors[deleteIndex] = tempActor;
	}
	for (int i = 0; i < deleteNum; ++i)
	{
		Actor* deleteActor = _actors.back();
		deleteActor->end();
		deleteActor->removeFromParent();
		_actors.pop_back();
	}
}
