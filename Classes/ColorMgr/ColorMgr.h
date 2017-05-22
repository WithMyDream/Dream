#ifndef __ColorMgr_H__
#define __ColorMgr_H__

#include "cocos2d.h"

using namespace cocos2d;

const int ColorNum = 5;

class ColorMgr : public Ref
{
public:
	ColorMgr();
	~ColorMgr();
	
	static ColorMgr* getInstance();
	
	bool init();

	const Color4B& getRandomColor();
	
private:
    int _indexs[ColorNum];
    int _currIndex;
};

#endif // __ColorMgr_H__
