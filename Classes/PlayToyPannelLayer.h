#pragma once
#include "BaseLayer.h"
#include "BaseToy.h"

class PlayToyPannelLayer:public BaseLayer
{
public:
	PlayToyPannelLayer();
	~PlayToyPannelLayer();
	virtual bool init();
	static PlayToyPannelLayer* create(ToyType type);
private:
	void onBackButtonClicked();
};