#include "BaseToy.h"

class ToyDragon:public BaseToy
{
public:
	ToyDragon();
	~ToyDragon();

	CREATE_FUNC(ToyDragon);
	virtual void onEnter();
	virtual void play();
};