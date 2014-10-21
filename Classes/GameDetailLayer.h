#pragma once
#include "BaseLayer.h"

class GameDetailLayer:public BaseLayer
{
public:
	GameDetailLayer();
	~GameDetailLayer();

	CREATE_FUNC(GameDetailLayer);
	virtual bool init();
	void showGameOver();

private:
	void onBackTouched();
	void onRestartTouched();
};