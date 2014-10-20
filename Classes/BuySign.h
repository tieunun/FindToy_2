#pragma once
#include "BaseNode.h"
#include "BaseToy.h"

class BuySign:public BaseNode
{
public:
	BuySign();
	~BuySign();
	CREATE_FUNC(BuySign);
	virtual bool init();
	void setToy(ToyType type);
	Sprite *getToy();
    ToyType getToyType();

private:
	Sprite *_frame;
	Vector<Sprite*> _toies;
	ToyType _type;
};