#include "BaseToy.h"

class ToyHelicopter:public BaseToy
{
public:
	ToyHelicopter();
	~ToyHelicopter();

	CREATE_FUNC(ToyHelicopter);
	virtual void onEnter();
	virtual void play();
};