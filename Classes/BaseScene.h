
#pragma once
#include "cocos2d.h"
	USING_NS_CC;
class BaseScene :
	public Scene
{
public:
	BaseScene(void);
	virtual ~BaseScene(void);

	virtual bool init();
};

