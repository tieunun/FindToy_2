#pragma once
#include "BaseToy.h"

class DragonEruption:public BaseToy
{
public:
	DragonEruption();
	~DragonEruption();
	virtual void onEnter();
	virtual void play();
	CREATE_FUNC(DragonEruption);
	void setEruptionFlipped(bool flipped);
};