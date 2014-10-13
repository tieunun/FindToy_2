#include "BaseToy.h"

class ToyGrab:public BaseToy
{
public:
	ToyGrab();
	~ToyGrab();

	CREATE_FUNC(ToyGrab);
	virtual void onEnter();
	virtual void play();
};