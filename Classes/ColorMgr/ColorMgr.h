#ifndef __ColorMgr_H__
#define __ColorMgr_H__

#include "cocos2d.h"

using namespace cocos2d;

class ColorMgr : public Ref
{
public:
	ColorMgr();
	~ColorMgr();
	
	static ColorMgr* getInstance();
	
	bool init();

	const Color4B& getRandomColor();
	
private:

};

#endif // __ColorMgr_H__
