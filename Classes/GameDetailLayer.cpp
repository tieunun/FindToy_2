
#include "GameDetailLayer.h"
#include "GameScene.h"

GameDetailLayer::GameDetailLayer()
{

}

GameDetailLayer::~GameDetailLayer()
{

}


bool GameDetailLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	auto bg = LayerColor::create(Color4B(128,128,128,128));
	bg->setContentSize(_winSize);
	this->addChild(bg);
	auto sub_bg = Sprite::createWithSpriteFrameName("common_game_over_0.png");
	sub_bg->setPosition(_winSize/2);
	this->addChild(sub_bg,1,11);
	auto button1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("common_back_ch_nor.png"),
		Sprite::createWithSpriteFrameName("common_back_ch_sel.png"),CC_CALLBACK_0(GameDetailLayer::onBackTouched,this));
	auto button2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("common_restart_ch_nor.png"),
		Sprite::createWithSpriteFrameName("common_restart_ch_sel.png"),CC_CALLBACK_0(GameDetailLayer::onRestartTouched,this));
	auto menu = Menu::create(button1,button2,NULL);
	menu->alignItemsHorizontallyWithPadding(100);
	menu->setPosition(155,10);
	menu->setScale(.8f);
	sub_bg->addChild(menu);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch *touch,Event *event)->bool{return this->isVisible()?true:false;};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    //this->showGameOver();
	return true;
}

void GameDetailLayer::showGameOver()
{
	SimpleAudioEngine::getInstance()->playEffect("common_fail.mp3");
	auto bg = (Sprite*)this->getChildByTag(11);
	auto animation = AnimationCache::getInstance()->getAnimation("game_over_animation");
	auto actions = Sequence::create(ScaleTo::create(0.0,0.0),
		ScaleTo::create(.22f,1.1f),ScaleTo::create(.12f,.9f),
		ScaleTo::create(.12f,1.0f),Animate::create(animation),NULL);
	bg->runAction(actions);
}

void GameDetailLayer::onBackTouched()
{
	Director::getInstance()->popScene();
}

void GameDetailLayer::onRestartTouched()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f,GameScene::create()));
}