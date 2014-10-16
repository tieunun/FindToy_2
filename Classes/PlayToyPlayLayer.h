#pragma once
#include "BaseLayer.h"
#include "BaseToy.h"

class PlayToyPlayLayer :public BaseLayer
{
public:
	PlayToyPlayLayer();
	~PlayToyPlayLayer();

	virtual bool init();
	static PlayToyPlayLayer *create(ToyType toyType);
	CC_PROPERTY(ToyType,_type,Type);
	void changeCloth(int index);
	void changeHair(int index);
	void onHelicopterReachCenter();
	void moveHelicopter();
	void update(float dt);
private:
	BaseToy *_toy;
	std::vector<Rect> _rects;
};