#pragma once
#include "BaseNode.h"
USING_NS_CC;

class ClothShelf:public BaseNode
{
public:
	ClothShelf();
	~ClothShelf();

	CREATE_FUNC(ClothShelf);
	virtual void onEnter();
private:
	Vector<Sprite *>_hairs;
	Vector<Sprite *>_clothes;
};