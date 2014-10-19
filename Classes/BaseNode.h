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
    CREATE_FUNC(BaseNode);
	virtual void onEnter();
protected:
	Rect getRectInGL(Node *node);
	int _onEnterCount;
};

