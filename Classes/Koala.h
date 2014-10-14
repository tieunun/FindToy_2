#pragma once
#include "BaseNode.h"
typedef enum KoalaState
{
	k_koala_normal = 0,
	k_koala_back,
	k_koala_move_right,
	k_koala_front_turn_right,
	k_koala_front_turn_left,
	k_koala_back_turn_left,
	k_koala_back_turn_right,
	k_koala_left_turn_back,
	k_koala_left_turn_front,
	k_koala_right_turn_front,
	k_koala_right_turn_back,
	k_koala_move_left,
	k_koala_drag_ladder_move,
	k_koala_up_ladder,
	k_koala_down_ladder,
	k_koala_down_with_gift
}KoalaState;
class Koala:public BaseNode
{
public:
	Koala();
	~Koala();
	CREATE_FUNC(Koala);

	virtual void onEnter();
	KoalaState getState() const;
	void setState(const KoalaState state);
	void move(Vec2 postion);
	
	CC_SYNTHESIZE(Vec2,_originPosition,OriginPosition);
    CC_SYNTHESIZE(Vec2,_lastPosition,LastPosition);


private:
	void onAnimationDone();
	FiniteTimeAction *getActionForState(const KoalaState state);
	FiniteTimeAction *getCallAction(KoalaState state);
	FiniteTimeAction *getDoneAction();
	void updateState();
	Sprite *_body;
	KoalaState _state;
	Vec2 _targetPosition;
	Vec2 _ladderPosition;
    bool _isKoalaAimate;
};