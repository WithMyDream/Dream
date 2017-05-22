#include "ColorMgr.h"

static ColorMgr* s_colorMgr = nullptr;

const Color4B Colors[ColorNum] =
{
	//Color4B(237, 232, 229, 255),
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
    for (int i=0; i<ColorNum; ++i) {
        _indexs[i] = i;
    }
    _currIndex = ColorNum - 1;
    
    return true;
}

const Color4B& ColorMgr::getRandomColor()
{
    if (_currIndex >= ColorNum - 1) {
        for (int i=0; i<ColorNum; ++i) {
            int rdm = (int)(CCRANDOM_0_1() * 1000000) % ColorNum;
            int temp = _indexs[i];
            _indexs[i] = _indexs[rdm];
            _indexs[rdm] = temp;
        }
        _currIndex = -1;
    }
    
    _currIndex++;
    
	return Colors[_indexs[_currIndex]];
}
