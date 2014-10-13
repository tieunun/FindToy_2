#pragma once
#include "BaseScene.h"
#include "GameMainBackground.h"
#include "GameStaticLayer.h"
class GameScene :
	public BaseScene
{
public:
	GameScene(void);
	virtual ~GameScene(void);

	virtual bool init();
	CREATE_FUNC(GameScene);

	void preloadResource();

private:
	GameMainBackground *_background;
	GameStaticLayer    *_staticLayer;
};