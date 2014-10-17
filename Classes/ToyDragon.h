#pragma once
#include "BaseToy.h"
#include "DragonEruption.h"

class ToyDragon:public BaseToy
{
public:
	ToyDragon();
	~ToyDragon();

	CREATE_FUNC(ToyDragon);
	virtual void onEnter();
	virtual void play();
	bool onDragonTouched(Touch *touch,Event *event);
private:
	void setDragonFlipped(bool flipped);
	DragonEruption *_eruption;
};