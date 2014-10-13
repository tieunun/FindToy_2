#include "BaseToy.h"

class ToyDoll:public BaseToy
{
public:
	ToyDoll();
	~ToyDoll();

	CREATE_FUNC(ToyDoll);
	virtual void onEnter();
	virtual void play();
};