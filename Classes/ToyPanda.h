#include "BaseToy.h"

class ToyPanda:public BaseToy
{
public:
	ToyPanda();
	~ToyPanda();

	CREATE_FUNC(ToyPanda);
	virtual void onEnter();
	virtual void play();
    
};