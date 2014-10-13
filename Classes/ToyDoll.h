#include "BaseToy.h"

class ToyDoll:public BaseToy
{
public:
	ToyDoll();
	~ToyDoll();

	CREATE_FUNC(ToyDoll);
	virtual void onEnter();
	virtual void play();
	void changeHair(int index);
	void changeCloth(int index);
private:
	Vector<Sprite*> _hairs;
	Vector<Sprite*> _clothes;
	Sprite *_hair;
	Sprite *_cloth;
};