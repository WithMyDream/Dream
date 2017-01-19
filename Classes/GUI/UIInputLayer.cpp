#include "UIInputLayer.h"
#include "../Logic/EventMgr.h"
//#include "Button.h"

#define PI 3.1415926

const Vec2 JoystickPos = Vec2(150, 150);

UIInputLayer::UIInputLayer()
: _joystickID(-1)
, _othersID(-1)
, _currToushes(0)
{
    
}

UIInputLayer::~UIInputLayer()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}

bool UIInputLayer::init()
{
	bool result = false;
	do {
		if (!Layer::init())
			break;
        
        _winSize = Director::getInstance()->getWinSize();
		
		_joystickBg = Sprite::create("GUI/joystick_bg.png");
		_joystickBg->setPosition(JoystickPos);
		addChild(_joystickBg);

		_joystickPoint = Sprite::create("GUI/joystick_center.png");
		_joystickPoint->setPosition(JoystickPos);
		addChild(_joystickPoint);
        
        Button* _button1 = Button::create("CloseNormal.png", "CloseSelected.png");
        _button1->setPosition(Vec2(_winSize.width - 200, 200));
        _button1->setScale(3.0f);
        _button1->setTag(1);
        _button1->addTouchEventListener(CC_CALLBACK_2(UIInputLayer::onClickButton, this));
        addChild(_button1);

		auto touchListener = EventListenerTouchAllAtOnce::create();
		// touchListener->setSwallowTouches(true);
		touchListener->onTouchesBegan = CC_CALLBACK_2(UIInputLayer::onTouchesBegan, this);
		touchListener->onTouchesMoved = CC_CALLBACK_2(UIInputLayer::onTouchesMoved, this);
		touchListener->onTouchesEnded = CC_CALLBACK_2(UIInputLayer::onTouchesEnded, this);
        touchListener->onTouchesCancelled = CC_CALLBACK_2(UIInputLayer::onTouchesCancelled, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

		result = true;
	} while (0);

	return result;
}

void UIInputLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    
    if (touches.empty())
        return;
    
    if (_currToushes >= 2)
        return;
    
    _currToushes++;

    Touch* touch = touches[0];
	Vec2 point = touch->getLocation();
    //CCLOG("[UIInputLayer::onTouchesBegan] [%d], %f, %f", touch->getID(), point.x, point.y);
	if (point.x <= _winSize.width/2.0f && _joystickID == -1)
    {
        _joystickID = touch->getID();
        joystickBegan(touch);
	}
    else
    {
        _othersID = touch->getID();
        othersBegan(touch);
    }
}

void UIInputLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    std::vector<Touch*>::const_iterator it = touches.begin();
    for ( ; it != touches.end(); ++it)
    {
        Touch* touch = *it;
        Vec2 point = touch->getLocation();
        //CCLOG("[UIInputLayer::onTouchesMoved] [%d], %f, %f", touch->getID(), point.x, point.y);
        if (touch->getID() == _joystickID)
            joystickMoved(touch);
        else if (touch->getID() == _othersID)
            othersMoved(touch);
    }
}

void UIInputLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    std::vector<Touch*>::const_iterator it = touches.begin();
    for ( ; it != touches.end(); ++it)
    {
        Touch* touch = *it;
        Vec2 point = touch->getLocation();
        //CCLOG("[UIInputLayer::onTouchesEnded] [%d], %f, %f", touch->getID(), point.x, point.y);
        if (touch->getID() == _joystickID)
        {
            _currToushes--;
            _joystickID = -1;
            joystickEnded(touch);
        }
        else if (touch->getID() == _othersID)
        {
            _currToushes--;
            _othersID = -1;
            othersEnded(touch);
        }
    }
}

void UIInputLayer::onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event)
{
    onTouchesEnded(touches, unused_event);
}

void UIInputLayer::joystickBegan(Touch *touch)
{
    joystickMoved(touch);
}

void UIInputLayer::joystickMoved(Touch *touch)
{
    Vec2 point = touch->getLocation();
    float y = point.y - JoystickPos.y;
    float x = point.x - JoystickPos.x;
    float angle = atan2(y, x) * 180 / PI;
    if (angle < 0)
        angle += 360.0f;    
    float jsBgRadis = _joystickBg->getContentSize().width * 0.5;
    float distanceOfTouchPointToCenter = sqrt(pow(JoystickPos.x - point.x, 2) + pow(JoystickPos.y - point.y, 2));
    if (distanceOfTouchPointToCenter >= jsBgRadis)
    {
        float deltX = x * (jsBgRadis / distanceOfTouchPointToCenter);
        float deltY = y * (jsBgRadis / distanceOfTouchPointToCenter);
        _joystickPoint->setPosition(Vec2(JoystickPos.x + deltX, JoystickPos.y + deltY));
    } else
        _joystickPoint->setPosition(point);
    
    EJoystick params(angle);
    EventMgr::getInatence()->notify(params);
}

void UIInputLayer::joystickEnded(Touch *touch)
{
    _joystickPoint->setPosition(JoystickPos);
    
    EJoystick params(-1);
    EventMgr::getInatence()->notify(params);
}

void UIInputLayer::othersBegan(Touch *touch)
{
    
}

void UIInputLayer::othersMoved(Touch *touch)
{
    
}

void UIInputLayer::othersEnded(Touch *touch)
{
    
}

void UIInputLayer::onClickButton(Ref* sender ,Widget::TouchEventType type)
{
    if (Widget::TouchEventType::BEGAN != type)
        return;
    
    Button* button = static_cast<Button*>(sender);
    
    EButton params(button->getTag());
    EventMgr::getInatence()->notify(params);
}
