
#include "GameDetailLayer.h"
#include "GameScene.h"
#include "GameStartScene.h"

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
//<<<<<<< Updated upstream

	_layers = LayerMultiplex::create();
	this->addChild(_layers);

    //this->showGameOver();
	this->initGameOver();
	this->initGamePause();
	return true;
}

void GameDetailLayer::initGameOver()
{
	_gameOver = Layer::create();
	_layers->addLayer(_gameOver);
//=======
//>>>>>>> Stashed changes
	auto sub_bg = Sprite::createWithSpriteFrameName("common_game_over_0.png");
	sub_bg->setPosition(_winSize/2);
	_gameOver->addChild(sub_bg,1,11);
	auto button1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("common_back_ch_nor.png"),
		Sprite::createWithSpriteFrameName("common_back_ch_sel.png"),CC_CALLBACK_0(GameDetailLayer::onBackTouched,this));
	button1->setTag(11);
	auto button2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("common_restart_ch_nor.png"),
		Sprite::createWithSpriteFrameName("common_restart_ch_sel.png"),CC_CALLBACK_0(GameDetailLayer::onRestartTouched,this));
	button2->setTag(12);
	auto menu = Menu::create(button1,button2,NULL);
	menu->alignItemsHorizontallyWithPadding(100);
	menu->setPosition(155,10);
	menu->setScale(.8f);
	sub_bg->addChild(menu);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch *touch,Event *event)->bool{return this->isVisible()?true:false;};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,_gameOver);
}

//<<<<<<< Updated upstream
void GameDetailLayer::initGamePause()
{
	_gamePause = Layer::create();
	_layers->addLayer(_gamePause);
	auto sub_bg = Sprite::create("common_pause.png");
	sub_bg->setPosition(_winSize/2);
	_gamePause->addChild(sub_bg,1,11);
	auto button1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("common_index_btn_nor.png"),
		Sprite::createWithSpriteFrameName("common_index_btn_sel.png"),CC_CALLBACK_0(GameDetailLayer::onBackTouched,this));
	button1->setTag(11);
	auto button2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("common_continue_btn_nor.png"),
		Sprite::createWithSpriteFrameName("comon_continue_btn_sel.png"),CC_CALLBACK_0(GameDetailLayer::onContinueTouched,this));
	button2->setTag(12);
	auto menu = Menu::create(button1,button2,NULL);
	menu->alignItemsHorizontallyWithPadding(100);
	menu->setPosition(155,10);
	menu->setScale(.8f);
	sub_bg->addChild(menu);


	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch *touch,Event *event)->bool{return this->isVisible()?true:false;};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,_gamePause);
//=======
    //this->showGameOver();
	return ;
//>>>>>>> Stashed changes
}

void GameDetailLayer::showGameOver()
{
	_layers->switchTo(0);
	SimpleAudioEngine::getInstance()->playEffect("common_fail.mp3");
//<<<<<<< Updated upstream
	auto bg = (Sprite*)_gameOver->getChildByTag(11);
//=======
	//auto bg = (Sprite*)this->getChildByTag(11);
//>>>>>>> Stashed changes
	auto animation = AnimationCache::getInstance()->getAnimation("game_over_animation");
	auto actions = Sequence::create(ScaleTo::create(0.0,0.0),
		ScaleTo::create(.22f,1.1f),ScaleTo::create(.12f,.9f),
		ScaleTo::create(.12f,1.0f),Animate::create(animation),NULL);
	bg->runAction(actions);
}

void GameDetailLayer::onBackTouched()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f,GameStartScene::create()));
}

void GameDetailLayer::onRestartTouched()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f,GameScene::create()));
}

void GameDetailLayer::onContinueTouched()
{
	Sprite *bg = (Sprite*)_gamePause->getChildByTag(11);
	Action *actions = Sequence::create(ScaleTo::create(0.12f,1.0f),
		ScaleTo::create(.12f,.9f),ScaleTo::create(.12f,1.1f),
		ScaleTo::create(.22f,0.0f)
		,CallFunc::create([=]{
			this->setVisible(false);
	auto scene = (GameScene*)this->getParent();
	scene->resumeGame();
	})
		,NULL);
	bg->runAction(actions);
}

void GameDetailLayer::showPause()
{
	_layers->switchTo(1);

	Sprite *bg = (Sprite*)_gamePause->getChildByTag(11);
	Action *actions = Sequence::create(ScaleTo::create(0.0,0.0),
		ScaleTo::create(.22f,1.1f),ScaleTo::create(.12f,.9f),
		ScaleTo::create(.12f,1.0f),NULL);
	bg->runAction(actions);
}