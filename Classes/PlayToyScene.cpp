#include "PlayToyScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

PlayToyScene::PlayToyScene()
{

}

PlayToyScene::~PlayToyScene()
{

}

PlayToyScene *PlayToyScene::create(ToyType toyType)
{
	auto scene = new PlayToyScene();
	scene->_toyType = toyType;
	scene->init();
	scene->autorelease();
	return scene;
}

bool PlayToyScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}


	_backgroundLayer = PlayToyBackground::create(_toyType);
	_playLayer		 = PlayToyPlayLayer::create(_toyType);
	_pannelLayer	 = PlayToyPannelLayer::create(_toyType);
	_detailLayer	 = PlayToyDetailLayer::create(_toyType);
	_detailLayer->setVisible(false);
	this->addChild(_backgroundLayer);
	this->addChild(_playLayer);
	this->addChild(_detailLayer);

	this->addChild(_pannelLayer);
	return true;
}

void PlayToyScene::moveBackground()
{
	_backgroundLayer->move();
}

void PlayToyScene::moveHelicopter()
{
	_playLayer->moveHelicopter();
}

void PlayToyScene::stopBackgroundMove()
{
    _backgroundLayer->stopAllActions();
}

void PlayToyScene::onEnter()
{
	BaseScene::onEnter();
	auto auido = SimpleAudioEngine::getInstance();
	switch (_toyType)
	{
	case k_toy_cap_pistol:
		auido->preloadEffect("cap_pistol_fire.mp3");
		auido->preloadEffect("cap_pistol_bullet_fire.mp3");
		break;
	case k_toy_harmonica:
		for (int i = 0;i<9;i++)
		{
			auido->preloadEffect(StringUtils::format("toy_harmonica_play_%d.mp3",i).c_str());
		}
		break;
	case k_toy_frog:
		auido->preloadEffect("toy_frog_croak.mp3");
		break;
	case k_toy_transformer:
		auido->preloadEffect("toy_transformer_fire.mp3");
		break;
	case k_toy_panda:
		auido->preloadEffect("toy_pander_cry.mp3");
		auido->preloadEffect("toy_pander_eat.mp3");
		auido->preloadEffect("toy_pander_tickle.mp3");
		auido->preloadEffect("toy_pander_sing.mp3");
		break;
	case k_toy_doll:
		auido->preloadEffect("toy_doll_cloth_click.mp3");
		auido->preloadEffect("change_cloth.mp3");
		break;
	case k_toy_helicopter:
		auido->preloadEffect("toy_helicopter_boom.mp3");
		auido->preloadEffect("toy_helicopter_flying.mp3");
		auido->preloadEffect("sound_success.mp3");
		auido->preloadEffect("common_fail.mp3");
		break;
	case k_toy_grab:
		auido->preloadEffect("toy_grab_run.mp3");
		break;
	case k_toy_dragon:
		auido->preloadEffect("toy_dragon_explode.mp3");
		break;
	case k_toy_chick:
		auido->preloadEffect("toy_chick_water.mp3");
		auido->preloadEffect("toy_chick_quack.mp3");
		break;
	default:
		break;
	}
}

void PlayToyScene::onExit()
{
	BaseScene::onExit();
	auto auido = SimpleAudioEngine::getInstance();
	switch (_toyType)
	{
	case k_toy_cap_pistol:
		auido->unloadEffect("cap_pistol_fire.mp3");
		auido->unloadEffect("cap_pistol_bullet_fire.mp3");
		break;
	case k_toy_harmonica:
		for (int i = 0;i<9;i++)
		{
			auido->unloadEffect(StringUtils::format("toy_harmonica_play_%d.mp3",i).c_str());
		}
	case k_toy_frog:
		auido->unloadEffect("toy_frog_croak.mp3");
		break;
	case k_toy_transformer:
		auido->unloadEffect("toy_transformer_fire.mp3");
		break;
	case k_toy_panda:
		auido->unloadEffect("toy_pander_cry.mp3");
		auido->unloadEffect("toy_pander_eat.mp3");
		auido->unloadEffect("toy_pander_tickle.mp3");
		auido->unloadEffect("toy_pander_sing.mp3");
		break;
	case k_toy_doll:
		auido->unloadEffect("toy_doll_cloth_click.mp3");
		auido->unloadEffect("change_cloth.mp3");
		break;
	case k_toy_helicopter:
		auido->unloadEffect("toy_helicopter_boom.mp3");
		//auido->unloadEffect("toy_helicopter_flying.mp3");
		auido->unloadEffect("sound_success.mp3");
		auido->unloadEffect("common_fail.mp3");
		break;
	case k_toy_grab:
		auido->unloadEffect("toy_grab_run.mp3");
		break;
	case k_toy_dragon:
		auido->unloadEffect("toy_dragon_explode.mp3");
		break;
	case k_toy_chick:
		auido->unloadEffect("toy_chick_water.mp3");
		auido->unloadEffect("toy_chick_quack.mp3");
		break;
	default:
		break;
	}
}

void PlayToyScene::showDetailWithSuccess(bool success)
{
	_detailLayer->setVisible(true);
	_detailLayer->showDetailWithSuceess(success);
}

Vec2 PlayToyScene::getBackgroundPosition() const
{
	return _backgroundLayer->getPosition();
}