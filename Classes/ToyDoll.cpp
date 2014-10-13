#include "ToyDoll.h"

ToyDoll::ToyDoll()
{
	_type = ToyType::k_toy_frog;
	_hair = NULL;
	_cloth = NULL;
}

ToyDoll::~ToyDoll()
{

}

void ToyDoll::onEnter()
{
	BaseNode::onEnter();

	auto name = GAME_DATA_STRING("toy_doll_hair_big");
	for ( int i = 0;i<3;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		_hairs.pushBack(Sprite::createWithSpriteFrameName(frame_name));
	}

	auto name = GAME_DATA_STRING("toy_doll_clothes");
	for ( int i = 0;i<6;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		_hairs.pushBack(Sprite::createWithSpriteFrameName(frame_name));
	}
}

void ToyDoll::play()
{

}

void ToyDoll::changeCloth(int index)
{
	if (_hair)
	{
		this->removeChild(_hair);
		_hair = _hairs.at(index);
		this->addChild(_hair,2);
	}
	else
	{

		_hair = _clothes.at(index);
		this->addChild(_hair,2);
	}
}

void ToyDoll::changeHair(int index)
{
	if (_cloth)
	{
		this->removeChild(_cloth);
		_cloth = _clothes.at(index);
		this->addChild(_hair,2);
	}
	else
	{
		_cloth = _clothes.at(index);
		this->addChild(_cloth,1);
	}
}