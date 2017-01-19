#ifndef __UIInputLayer_H__
#define __UIInputLayer_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

class UIInputLayer: public Layer
{
public:
    CREATE_FUNC(UIInputLayer)
    
    UIInputLayer();
    ~UIInputLayer();
    bool init();

protected:
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event);

private:
    void joystickBegan(Touch *touch);
    void joystickMoved(Touch *touch);
    void joystickEnded(Touch *touch);
    
    void othersBegan(Touch *touch);
    void othersMoved(Touch *touch);
    void othersEnded(Touch *touch);
    
    void onClickButton(Ref* sender, Widget::TouchEventType type);

private:
    Size    _winSize;
    int     _joystickID;
    int     _othersID;
    int     _currToushes;
	Sprite* _joystickBg;
	Sprite* _joystickPoint;
};

#endif /* __UIInputLayer_H__ */
