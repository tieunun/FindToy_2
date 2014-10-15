#pragma once
#include "BaseNode.h"

typedef enum
{
	k_toy_cap_pistol,   //玩具枪
	k_toy_harmonica,    //口琴
	k_toy_frog,			//青蛙
	k_toy_transformer,	//变形金刚
	k_toy_panda,		//熊猫
	k_toy_doll,			//洋娃娃
	k_toy_helicopter,	//飞机
	k_toy_grab,			//挖掘机
	k_toy_dragon,		//龙
	k_toy_chick,		//小鸡
	k_toy_count			//总数
}ToyType;
class BaseToy :
	public BaseNode
{
public:
	BaseToy(void);
	virtual ~BaseToy(void);

	virtual void onEnter();

	virtual void play();

	static BaseToy *create(ToyType type);
	static BaseToy *createBig(ToyType type);

protected:
	ToyType _type;
	Sprite *_body;
	virtual bool OnToyTouched(Touch *touch,Event *event);
	bool _toyAnimate;
};

