#pragma once
#include "BaseLayer.h"
class GameMainBackground :
	public BaseLayer
{
public:
	GameMainBackground(void);
	~GameMainBackground(void);
	virtual bool init();

	CREATE_FUNC(GameMainBackground);
};