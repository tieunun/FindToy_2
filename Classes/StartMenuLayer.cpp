#include "StartMenuLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

StartMenuLayer::StartMenuLayer()
{

}

StartMenuLayer::~StartMenuLayer()
{

}

bool StartMenuLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	auto bg = Sprite::create("start_background.jpg");
	bg->setPosition(_winSize/2);
	this->addChild(bg);

	auto title = Sprite::create("start_title.png");
	this->addChild(title);
	title->setPosition(778,490);

	auto rotate1 = RotateBy::create(.6f,3);
	auto rotate2 = RotateBy::create(1.2f,-6);
	title->runAction(RepeatForever::create(Sequence::create(rotate1,rotate2,rotate1,NULL)));

	auto move1 = MoveBy::create(.6f,Vec2(-10,0));
	auto move2 = MoveBy::create(1.2f,Vec2(20,0));
	title->runAction(RepeatForever::create(Sequence::create(move1,move2,move1,NULL)));

	auto startItem = MenuItemImage::create("start_btn_nor.png","start_btn_sel.png",CC_CALLBACK_0(StartMenuLayer::onStartTouched,this));
	auto menu = Menu::create(startItem,NULL);
	startItem->setAnchorPoint(Vec2(1,.1));
	this->addChild(menu,1,1);

	auto pop = Sequence::create(DelayTime::create(2),ScaleTo::create(.2,1.1),ScaleTo::create(.2,0.9),ScaleTo::create(.2,1.1),
		ScaleTo::create(.2,1),DelayTime::create(4),NULL);
	startItem->runAction(RepeatForever::create(pop));

	menu->setPosition(900,110);

	return true;
}

void StartMenuLayer::onStartTouched()
{
	auto menu = (Menu*)this->getChildByTag(1);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	auto scene = GameScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
}