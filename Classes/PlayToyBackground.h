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
private:
	ToyType _type;
};