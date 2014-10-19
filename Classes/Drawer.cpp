#include "Drawer.h"
#include "ui/UIButton.h"
#include "Shelf.h"
using namespace cocos2d::ui;

Drawer::Drawer(void)
{
    _toyType = (ToyType)-1;
}


Drawer::~Drawer(void)
{
}

void Drawer::onEnter()
{
	BaseNode::onEnter();

	if (_onEnterCount >1)
	{
		return;
	}
	auto nor = GAME_DATA_STRING("drawer_nor");
	auto sel = GAME_DATA_STRING("drawer_sel");
	//auto body = MenuItemSprite::create(Sprite::createWithSpriteFrameName(nor),Sprite::createWithSpriteFrameName(sel),CC_CALLBACK_0(Drawer::onDrawerTouched,this));
	auto button = Button::create(nor,sel,"",Widget::TextureResType::PLIST);
	button->addTouchEventListener(this,toucheventselector(Drawer::onDrawerTouched));
	this->addChild(button);
}

void Drawer::onDrawerTouched(Ref *pSender,TouchEventType type)
{
	//auto button = (Button*)pSender;
	switch (type)
	{
	case ui::TOUCH_EVENT_ENDED:
        {
            auto shelf = (Shelf *)(this->getParent()->getParent());
            shelf->onDrawerTouched(this->getDrawerPosition());
        }
		//to do
		break;
	default:
		break;
	}
}
