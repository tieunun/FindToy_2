#include "BaseToy.h"

typedef enum PandaState
{
	k_panda_tickle,	//Ñ÷
	k_panda_cry,	//¿Þ
	k_panda_smile,	//Ð¦	
	k_panda_eat,		//³ÔÖñ×Ó
	k_panda_none

}PandaState;
class ToyPanda:public BaseToy
{
public:
	ToyPanda();
	~ToyPanda();

	CREATE_FUNC(ToyPanda);
	virtual void onEnter();
	virtual void play();
	CC_PROPERTY(PandaState,_state,State);
private:

	bool onPandaTouched(Touch *touch,Event *event);
	void onAnimateDone();
	Sprite *_head;
	Sprite *_downPart;
	Sprite *_hand;
};