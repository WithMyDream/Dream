#include "ColorMgr.h"

static ColorMgr* s_colorMgr = nullptr;

const int ColorNum = 6;
const Color4B Colors[ColorNum] =
{
	Color4B(237, 232, 229, 255),
	Color4B(220, 201, 194, 255),
	Color4B(179, 151, 147, 255),
	Color4B(113, 94, 88, 255),
	Color4B(80, 132, 130, 255),
	Color4B(171, 222, 217, 255),
};

ColorMgr::ColorMgr()
{
    
}

ColorMgr::~ColorMgr()
{
	
}

ColorMgr* ColorMgr::getInstance()
{
	if (!s_colorMgr)
	{
		s_colorMgr = new ColorMgr();
		s_colorMgr->init();
	}

	return s_colorMgr;
}

bool ColorMgr::init()
{
	
    
    return true;
}

const Color4B& ColorMgr::getRandomColor()
{
	int index = (int)(CCRANDOM_0_1() * 1000000) % ColorNum;
	return Colors[index];
}