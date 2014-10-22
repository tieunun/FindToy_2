#pragma once
#include "BaseScene.h"
#include "StartMenuLayer.h"

class GameStartScene:public BaseScene
{
public:
	GameStartScene();
	~GameStartScene();
	virtual bool init();
	CREATE_FUNC(GameStartScene);
	void preloadResource();
private:
	void loadKoalaAnimation();
	void loadAudio();
	void loadBuyerAnimation();
	StartMenuLayer *_menuLayer;
};