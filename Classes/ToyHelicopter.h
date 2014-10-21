#include "BaseToy.h"

#define Toy_Helicopter_Gravity 80
#define  Max_Down_Height 100000
#define Toy_Helicopter_H_Speed 100
class ToyHelicopter:public BaseToy
{
public:
	ToyHelicopter();
	~ToyHelicopter();

	CREATE_FUNC(ToyHelicopter);
	virtual void onEnter();
	virtual void play();
	void explode();

private:
	bool onHelicopterTouchBegin(Touch *touch,Event *event);
	void onHelicopterTouchMove(Touch *touch,Event *event);
};