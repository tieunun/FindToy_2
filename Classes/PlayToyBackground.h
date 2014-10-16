#pragma once
#include "BaseLayer.h"
#include "BaseToy.h"

class PlayToyBackground :public BaseLayer
{
public:
	PlayToyBackground();
	~PlayToyBackground();

	virtual bool init();
	static PlayToyBackground *create(ToyType toyType);
	void move();
private:
	ToyType _type;
};