#include "BaseToy.h"

#define Toy_Helicopter_Gravity 20
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
	std::vector<Rect> getHelicopterContentRects();
private:
	bool onHelicopterTouchBegin(Touch *touch,Event *event);
	void onHelicopterTouchMove(Touch *touch,Event *event);

	std::vector<Rect> _contentRects;
};