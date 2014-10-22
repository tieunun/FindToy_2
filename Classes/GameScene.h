#pragma once
#include "BaseScene.h"
#include "GameMainBackground.h"
#include "GameStaticLayer.h"
#include "ToyLayer.h"
#include "GameTimeLayer.h"
#include "GameDetailLayer.h"
enum GameState
{
	k_game_pause,
	k_game_running
};
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
	void showGameOver();
	void showPause();
	void resumeGame();
    void handInToy(ToyType type);
    virtual void onEnter();
	virtual void onExit();
	void setDrawerShouldTouch(bool touch);

	CC_SYNTHESIZE(GameStaticLayer*,_staticLayer,StaticLayer);

private:

	void pauseGame();
	void operationAllSchedulerAndActions(Node *node,GameState state);
	void loadKoalaAnimation();
	void loadAudio();
	void loadBuyerAnimation();
	GameMainBackground *_background;
    ToyLayer           *_toyLayer;
	GameTimeLayer	   *_timerLayer;
	GameDetailLayer		*_detailLayer;
};