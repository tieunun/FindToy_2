#include "BaseScene.h"
#include "BaseToy.h"
#include "PlayToyBackground.h"
#include "PlayToyPlayLayer.h"

class PlayToyScene :public BaseScene
{
public:
	PlayToyScene();
	~PlayToyScene();

	static PlayToyScene *create(ToyType toyType);
	virtual bool init();
	void moveBackground();
	void moveHelicopter();
    void stopBackgroundMove();
private:
	ToyType _toyType;
	PlayToyBackground *_backgroundLayer;
	PlayToyPlayLayer  *_playLayer;
};