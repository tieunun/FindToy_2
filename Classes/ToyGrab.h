#pragma once
#include "BaseToy.h"
#include "ToyGrabber.h"
class ToyGrab:public BaseToy
{
public:
	ToyGrab();
	~ToyGrab();

	CREATE_FUNC(ToyGrab);
	virtual void onEnter();
	virtual void play();
    bool onGrabTouched(Touch *touch,Event *event);
private:
	void setGrabFlippedX(bool flipped);
    ToyGrabber *_grabber;
};