#pragma once
#include "BaseToy.h"

class PopToy:public BaseNode
{
public:
	PopToy();
	~PopToy();

	CREATE_FUNC(PopToy);
	virtual void onEnter();
	bool isPoped(Vec2 popPos);
	void popToy(ToyType type);
private:
	Vector<BaseToy*> _toies;
	Sprite *_body;
	std::vector<Vec2> _pops;
};
