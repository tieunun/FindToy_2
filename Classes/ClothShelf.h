#pragma once
#include "BaseNode.h"
USING_NS_CC;
#include "ui/UIButton.h"
using namespace ui;

class ClothShelf:public BaseNode
{
public:
	ClothShelf();
	~ClothShelf();

	CREATE_FUNC(ClothShelf);
	virtual void onEnter();
private:
	Vector<Button *>_hairs;
	Vector<Button *>_clothes;
};