#pragma once
#include "BaseLayer.h"

class StartMenuLayer:public BaseLayer
{
public:
	StartMenuLayer();
	~StartMenuLayer();

	CREATE_FUNC(StartMenuLayer);
	virtual bool init();
private:
	void onStartTouched();
};