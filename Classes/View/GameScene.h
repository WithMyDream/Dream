#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include <vector>
#include "Actor.h"
#include "../Logic/EventMgr.h"
#include "B2DebugDrawLayer.h"

using namespace cocos2d;

class GameScene : public Node
{
public:
    static GameScene* create();
    
    GameScene();
    ~GameScene();
    bool init() override;
    
    void setDebugDraw(b2World* b2word);
	void setDebugDrawVisible(bool isVisible);
    
    void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
    
    void onLoadMap(EventParams &params);
    void onCreateUnit(EventParams &params);
	void onCreateRope(EventParams &params);
	void onDestroyUnit(EventParams &params);
	void onSetMainUnit(EventParams &params);
    void onJoystick(EventParams &params);

	Actor* findActorWithUnit(Unit* unit);
    
    void update(float dt) override;
    
private:
    
    
private:
    std::vector<Actor*> _actors;
	std::vector<int> _deleteActorIndexs;
    
    Node* _bgNode;
    B2DebugDrawLayer*   _debugDrawLayer;
};

#endif // __GameScene_H__
