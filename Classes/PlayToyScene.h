#include "BaseScene.h"
#include "BaseToy.h"
#include "PlayToyBackground.h"
#include "PlayToyPlayLayer.h"
#include "PlayToyPannelLayer.h"

class PlayToyScene :public BaseScene
{
public:
	PlayToyScene();
	~PlayToyScene();

	static PlayToyScene *create(ToyType toyType);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void moveBackground();
	void moveHelicopter();
    void stopBackgroundMove();
private:
	void preLoadAudioAndEffect();
	ToyType _toyType;
	PlayToyBackground *_backgroundLayer;
	PlayToyPlayLayer  *_playLayer;
	PlayToyPannelLayer *_pannelLayer;
};