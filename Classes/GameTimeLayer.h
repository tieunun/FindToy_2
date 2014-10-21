#pragma once
#include "BaseLayer.h"
#include "GameTimer.h"

class GameTimeLayer:public BaseLayer
{
public:
	GameTimeLayer();
	~GameTimeLayer();
	CREATE_FUNC(GameTimeLayer);
	virtual bool init();
	virtual void onEnter();
	void showGameOver();
private:
	GameTimer *_gameTimer;
};