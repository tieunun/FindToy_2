#pragma once
#include"cocos2d.h"
#include "GameData.h"
#include "BaseToy.h"
using namespace cocos2d;
class BaseLayer :
	public Layer
{
public:
	BaseLayer(void);
	virtual ~BaseLayer(void);

	virtual bool init();
	Vec2 getPositionInWinSize(const Vec2 &position);
protected:
	Size _winSize;
	ToyType _type;
};

