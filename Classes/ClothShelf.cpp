#include "ClothShelf.h"

ClothShelf::ClothShelf()
{

}

ClothShelf::~ClothShelf()
{

}

void ClothShelf::onEnter()
{
	BaseNode::onEnter();

	auto name = GAME_DATA_STRING("toy_doll_hair_small");
	for ( int i = 0;i<3;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		_hairs.pushBack(Sprite::createWithSpriteFrameName(frame_name));
		//this->addChild()
	}

	auto name = GAME_DATA_STRING("toy_doll_clothes_small");
	for ( int i = 0;i<6;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		_hairs.pushBack(Sprite::createWithSpriteFrameName(frame_name));
	}


}