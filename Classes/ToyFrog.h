#include "BaseToy.h"

class ToyFrog:public BaseToy
{
public:
	ToyFrog();
	~ToyFrog();

	CREATE_FUNC(ToyFrog);
	virtual void onEnter();
	virtual void play();
private:
	Sprite *_speeder;
};