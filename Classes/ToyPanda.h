#include "BaseToy.h"

typedef enum PandaState
{
	k_panda_tickle,	//��
	k_panda_cry,	//��
	k_panda_smile,	//Ц	
	k_panda_eat,		//������
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