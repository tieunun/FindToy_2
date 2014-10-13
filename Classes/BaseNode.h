#pragma once
#include "cocos2d.h"
#include "GameData.h"
USING_NS_CC;
class BaseNode :
	public Node
{
public:
	BaseNode(void);
	virtual ~BaseNode(void);

	virtual void onEnter();
};

