#include "PlayToyDetailLayer.h"
#include "PlayToyScene.h"

PlayToyDetailLayer::PlayToyDetailLayer()
{

}

PlayToyDetailLayer::~PlayToyDetailLayer()
{

}

PlayToyDetailLayer *PlayToyDetailLayer::create(ToyType type)
{
	auto layer = new PlayToyDetailLayer();
	layer->setToyType(type);
	layer->init();
	layer->autorelease();
	return layer;
}

bool PlayToyDetailLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	auto bg = LayerColor::create(Color4B(128,128,128,128));
	bg->setContentSize(_winSize);
	this->addChild(bg);

	switch (_toyType)
	{
	case k_toy_helicopter:
		{
		auto sub_bg = Sprite::createWithSpriteFrameName("common_game_over_0.png");
		sub_bg->setPosition(_winSize/2);
		this->addChild(sub_bg,1,11);
		auto button1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("common_back_ch_nor.png"),
			Sprite::createWithSpriteFrameName("common_back_ch_sel.png"),CC_CALLBACK_0(PlayToyDetailLayer::onBackTouched,this));
		auto button2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("common_restart_ch_nor.png"),
			Sprite::createWithSpriteFrameName("common_restart_ch_sel.png"),CC_CALLBACK_0(PlayToyDetailLayer::onRestartTouched,this));
		auto menu = Menu::create(button1,button2,NULL);
		menu->alignItemsHorizontallyWithPadding(100);
		menu->setPosition(155,10);
		menu->setScale(.8f);
		sub_bg->addChild(menu);
		}
		break;
	default:
		break;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch *touch,Event *event)->bool{return this->isVisible()?true:false;};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void PlayToyDetailLayer::showDetailWithSuceess(bool success)
{
	auto bg = (Sprite*)this->getChildByTag(11);

	if (success)
	{
		SimpleAudioEngine::getInstance()->playEffect("sound_success.mp3");
        auto animation = Animation::create();
        animation->addSpriteFrameWithFile("common_game_victory_0.png");
        animation->addSpriteFrameWithFile("common_game_victory_1.png");
        animation->setRestoreOriginalFrame(false);
        animation->setDelayPerUnit(.2f);
        animation->setLoops(-1);
        bg->runAction(Animate::create(animation));
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("common_fail.mp3");
        auto animation = AnimationCache::getInstance()->getAnimation("game_over_animation");
        bg->runAction(Animate::create(animation));
	}
}

void PlayToyDetailLayer::onBackTouched()
{
	Director::getInstance()->popScene();
}

void PlayToyDetailLayer::onRestartTouched()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f,PlayToyScene::create(_toyType)));
}