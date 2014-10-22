#pragma once
#include "BaseNode.h"

class GameTimer:public BaseNode
{
public:
	GameTimer();
	~GameTimer();

	virtual bool init();
	virtual void onEnter();
	virtual void update(float dt);
	CREATE_FUNC(GameTimer);
	CC_SYNTHESIZE(float,_time,Time);
	CC_SYNTHESIZE(float,_speed,Speed);
	void BeginToTime(float time=0);
private:
	ProgressTimer *_timer;
	Label *_label;
};