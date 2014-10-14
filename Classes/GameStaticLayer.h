#pragma once
#include "BaseLayer.h"

class GameStaticLayer :public BaseLayer
{
public:
	GameStaticLayer();
	~GameStaticLayer();

	CREATE_FUNC(GameStaticLayer);
	virtual bool init();
    
    void onDrawerTouched(Vec2 position);
    bool abcdefg(Touch *touch, Event *unusedEvent);
};