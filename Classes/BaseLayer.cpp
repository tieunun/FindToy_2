#include "BaseLayer.h"


BaseLayer::BaseLayer(void)
{
}


BaseLayer::~BaseLayer(void)
{
}

bool BaseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_winSize = Director::getInstance()->getWinSize();
	return true;
}

Vec2 BaseLayer::getPositionInWinSize(const Vec2 &position)
{
	return Vec2(_winSize.width * position.x,_winSize.height * position.y);
}