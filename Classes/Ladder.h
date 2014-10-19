#pragma once
#include "BaseNode.h"

class Ladder :public BaseNode
{
public:
	Ladder();
	~Ladder();
	CREATE_FUNC(Ladder);
	virtual void onEnter();
    CC_SYNTHESIZE(int, _ladderPos, LadderPos);
};