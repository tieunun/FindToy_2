#include "ClothShelf.h"
#include "ui/UIButton.h"
using namespace ui;

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
		auto hair = Button::create(frame_name,frame_name,"",Widget::TextureResType::PLIST);
		//auto hair = Sprite::createWithSpriteFrameName(frame_name);
		hair->setPosition(Vec2(-191+i*191,-191));
		_hairs.pushBack(hair);
		//this->addChild()
	}

	name = GAME_DATA_STRING("toy_doll_clothes_small");
	for ( int i = 0;i<6;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		auto cloth = Button::create(frame_name,frame_name,"",Widget::TextureResType::PLIST);
		cloth->setPosition(Vec2(-191+191*i%3,191*(i/3)));
		_hairs.pushBack(cloth);
	}
}