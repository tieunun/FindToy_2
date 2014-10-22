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
	void showPause();
private:
	void initGameOver();
	void initGamePause();
	void onBackTouched();
	void onRestartTouched();
	void onContinueTouched();
	LayerMultiplex *_layers;
	Layer *_gamePause;
	Layer *_gameOver;
};