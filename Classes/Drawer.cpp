#include "Drawer.h"
#include "Shelf.h"

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

	_temp = Sprite::create();
	this->addChild(_temp);

	auto nor = GAME_DATA_STRING("drawer_nor");
	auto sel = GAME_DATA_STRING("drawer_sel");
	//auto body = MenuItemSprite::create(Sprite::createWithSpriteFrameName(nor),Sprite::createWithSpriteFrameName(sel),CC_CALLBACK_0(Drawer::onDrawerTouched,this));
	_button = Button::create(nor,sel,"",Widget::TextureResType::PLIST);
	_button->addTouchEventListener(this,toucheventselector(Drawer::onDrawerTouched));
	this->addChild(_button);

}

void Drawer::onDrawerTouched(Ref *pSender,TouchEventType type)
{
	//auto button = (Button*)pSender;
	switch (type)
	{
	case ui::TOUCH_EVENT_ENDED:
        {
            auto shelf = (Shelf *)(this->getParent());
            shelf->onDrawerTouched(this->getDrawerPosition());
        }
	case ui::TOUCH_EVENT_BEGAN:
		{
			SimpleAudioEngine::getInstance()->playEffect("drawer_click.mp3");
		}
		//to do
		break;
	default:
		break;
	}
}

void Drawer::open()
{
	//_temp->stopAllActions();
	SimpleAudioEngine::getInstance()->playEffect("drawer_open.mp3");
	auto animation = AnimationCache::getInstance()->getAnimation("drawer_animation");
	_button->setVisible(false);
	auto animate = Animate::create(animation);
	_temp->runAction(Sequence::create(animate,DelayTime::create(.6f),
		CallFunc::create([=](){
			SimpleAudioEngine::getInstance()->playEffect("drawer_open.mp3");
	}),
		animate->reverse()
		,CallFunc::create([=](){
			_button->setVisible(true);
	})
		,NULL));
}
