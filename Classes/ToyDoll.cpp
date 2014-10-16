#include "ToyDoll.h"
#include "PlayToyScene.h"

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

	auto defaut_name = GAME_DATA_STRING("toy_doll_empty");
	_body = Sprite::createWithSpriteFrameName(defaut_name);
	this->addChild(_body);

	auto name = GAME_DATA_STRING("toy_doll_hair_big");
	for ( int i = 0;i<3;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		_hairs.pushBack(Sprite::createWithSpriteFrameName(frame_name));
	}

    name = GAME_DATA_STRING("toy_doll_cloth_big");
	for ( int i = 0;i<6;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		_clothes.pushBack(Sprite::createWithSpriteFrameName(frame_name));
	}
}

void ToyDoll::play()
{
}

void ToyDoll::changeHair(int index)
{
	auto pos_name = StringUtils::format("toy_doll_hair_pos_%d",index);
	auto pos = GAME_DATA_POINT(pos_name);
	if (_hair)
	{
		this->removeChild(_hair);
		_hair = _hairs.at(index);
		this->addChild(_hair,2);
	}
	else
	{
		_body->setSpriteFrame(GAME_DATA_STRING("toy_doll_empty"));
		_hair = _hairs.at(index);
		this->addChild(_hair,2);
	}
	_hair->setPosition(pos);
}

void ToyDoll::changeCloth(int index)
{
	auto pos_name = StringUtils::format("toy_doll_cloth_pos_%d",index);
	auto pos = GAME_DATA_POINT(pos_name);
	if (_cloth)
	{
		this->removeChild(_cloth);
		_cloth = _clothes.at(index);
		this->addChild(_cloth,1);
	}
	else
	{
		_cloth = _clothes.at(index);
		this->addChild(_cloth,1);
	}
	_cloth->setPosition(pos);
}