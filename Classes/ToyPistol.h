#pragma once
#include "BaseToy.h"
#include "ToyBullet.h"
class ToyPistol :
	public BaseToy
{
public:
	ToyPistol(void);
	~ToyPistol(void);

	CREATE_FUNC(ToyPistol);
	virtual void onEnter();
	void play();

private:
	bool OnToyTouched(Touch *touch,Event *event);
    ToyBullet *_bullet;
};

