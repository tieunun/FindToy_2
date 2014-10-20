#include "ClothShelf.h"
#include "ui/UIButton.h"
#include "PlayToyPlayLayer.h"
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

	if (_onEnterCount >1)
	{
		return;
	}
	auto name = GAME_DATA_STRING("toy_doll_hair_small");
	for ( int i = 0;i<3;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		auto hair = Button::create(frame_name,frame_name,"",Widget::TextureResType::PLIST);
		//auto hair = Sprite::createWithSpriteFrameName(frame_name);
		hair->setPosition(Vec2(-191+i*191,191));
		hair->addTouchEventListener(this,toucheventselector(ClothShelf::clothesTouched));
		_hairs.pushBack(hair);
		hair->setTag(i+1);
		this->addChild(hair,i+1);
	}

	name = GAME_DATA_STRING("toy_doll_cloth_small");
	for ( int i = 0;i<6;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		auto cloth = Button::create(frame_name,frame_name,"",Widget::TextureResType::PLIST);
		cloth->setPosition(Vec2(-191+191*(i%3),-201*(i/3)));
		cloth->addTouchEventListener(this,toucheventselector(ClothShelf::clothesTouched));
		_clothes.pushBack(cloth);
		cloth->setTag(4+i);
		this->addChild(cloth);
		//-180+i*180,-212
	}
}

void ClothShelf::clothesTouched(Ref *pSender,TouchEventType type)
{
	Button* butten = (Button*)pSender;
	unsigned int tag = butten->getTag();  
	switch (type)  
	{  
	case TOUCH_EVENT_BEGAN:  
		{
			SimpleAudioEngine::getInstance()->playEffect("toy_doll_cloth_click.mp3");
			butten->setScale(1.1f);
			auto layer = (PlayToyPlayLayer*)this->getParent();
			if (tag >3)
			{
				layer->changeCloth(tag-4);
			}
			else
			{
				layer->changeHair(tag-1);
			}
		}
		break;  
	case TOUCH_EVENT_ENDED:
		butten->setScale(1);
		break;
	case TOUCH_EVENT_CANCELED:
		butten->setScale(1);
		break;
	default:  
		break;  
	}  
}

