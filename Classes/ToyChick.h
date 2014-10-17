#include "BaseToy.h"

class ToyChick:public BaseToy
{
public:
	ToyChick();
	~ToyChick();

	CREATE_FUNC(ToyChick);
	virtual void onEnter();
	virtual void play();
	bool onChickTouched(Touch *touch,Event *event);
};