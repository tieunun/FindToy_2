#pragma once
#include "BaseNode.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

typedef enum
{
	k_toy_cap_pistol,   //���ǹ
	k_toy_harmonica,    //����
	k_toy_frog,			//����
	k_toy_transformer,	//���ν��
	k_toy_panda,		//��è
	k_toy_doll,			//������
	k_toy_helicopter,	//�ɻ�
	k_toy_grab,			//�ھ��
	k_toy_dragon,		//��
	k_toy_chick,		//С��
	k_toy_count			//����
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
	CC_SYNTHESIZE(bool,_toyAnimate,ToyAnimate);
	Rect getBox();
	virtual void setToyOpacity(int opticy);
	virtual Action* createFadeOutAction(bool fadeOut);
    Sprite *getBody() const;

protected:
	ToyType _type;
	Sprite *_body;
	virtual bool OnToyTouched(Touch *touch,Event *event);
};

