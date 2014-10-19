#pragma once
#include "BaseScene.h"
#include "GameMainBackground.h"
#include "GameStaticLayer.h"
#include "ToyLayer.h"
class GameScene :
	public BaseScene
{
public:
	GameScene(void);
	virtual ~GameScene(void);

	virtual bool init();
	CREATE_FUNC(GameScene);

	void preloadResource();
    
    void moveKoala(Vec2 position);              //automatic find the way
    void openDrawer(Vec2 position);
    void handInToy(ToyType type);
    
	void setDrawerShouldTouch(bool touch);

private:

	void loadKoalaAnimation();
	GameMainBackground *_background;
	GameStaticLayer    *_staticLayer;
    ToyLayer           *_toyLayer;
};