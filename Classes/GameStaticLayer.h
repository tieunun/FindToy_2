#include "BaseLayer.h"

class GameStaticLayer :public BaseLayer
{
public:
	GameStaticLayer();
	~GameStaticLayer();

	CREATE_FUNC(GameStaticLayer);
	virtual bool init();
    
    bool abcdefg(Touch *touch, Event *unusedEvent);
};