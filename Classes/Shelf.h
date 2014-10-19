#pragma once
#include "BaseNode.h"
#include "Drawer.h"

class Shelf:public BaseNode
{
public:
	Shelf();
	~Shelf();

	CREATE_FUNC(Shelf);
	virtual void onEnter();
    void onDrawerTouched(Vec2 position);
    void openDrawer(Vec2 position);

private:
	Sprite *_body;
	Vector<Drawer*> _drawers;
};