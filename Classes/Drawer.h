#pragma once
#include "BaseNode.h"
#include "ui/UIWidget.h"

class Drawer :
	public BaseNode
{
public:
	Drawer(void);
	~Drawer(void);

	CREATE_FUNC(Drawer);

	virtual void onEnter();
	//virtual void init()
	void onDrawerTouched(Ref *pSender,ui::TouchEventType type);
    CC_SYNTHESIZE(Vec2, _drawerPosition, DrawerPosition);
};

