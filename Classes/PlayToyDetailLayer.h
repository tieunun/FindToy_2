#pragma once
#include "BaseLayer.h"

class PlayToyDetailLayer:public BaseLayer
{
public:
	PlayToyDetailLayer();
	~PlayToyDetailLayer();

	static PlayToyDetailLayer* create(ToyType type);
	virtual bool init();
	CC_SYNTHESIZE(ToyType,_toyType,ToyType);

	void showDetailWithSuceess(bool success);
private:
	void onBackTouched();
	void onRestartTouched();
};