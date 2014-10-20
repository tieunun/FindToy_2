#include "ToyDoll.h"
#include "PlayToyScene.h"

ToyDoll::ToyDoll()
{
	_type = ToyType::k_toy_frog;
	_hair = NULL;
	_cloth = NULL;
    _toyAnimate = false;
}

ToyDoll::~ToyDoll()
{

}

void ToyDoll::onEnter()
{
	BaseNode::onEnter();

    _emitter = ParticleSystemQuad::create("change_cloth.plist");
    _emitter->setPosition(-60,190);
    this->addChild(_emitter);
    _emitter->setVisible(false);
    
	auto defaut_name = GAME_DATA_STRING("toy_doll_empty");
	_body = Sprite::createWithSpriteFrameName(defaut_name);
	this->addChild(_body);

	auto name = GAME_DATA_STRING("toy_doll_hair_big");
	for ( int i = 0;i<3;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
		_hairs.pushBack(Sprite::createWithSpriteFrameName(frame_name));
	}

    name = GAME_DATA_STRING("toy_doll_cloth_big");
	for ( int i = 0;i<6;i++)
	{
		auto frame_name = StringUtils::format(name.c_str(),i);
        auto progress = ProgressTimer::create(Sprite::createWithSpriteFrameName(frame_name));
        progress->setMidpoint(Vec2(0,1));
        progress->setBarChangeRate(Vec2(0,1));
        progress->setPercentage(0);
        progress->setType(ProgressTimer::Type::BAR);
		_clothes.pushBack(progress);
	}

}

void ToyDoll::play()
{
}

void ToyDoll::changeHair(int index)
{
	auto pos_name = StringUtils::format("toy_doll_hair_pos_%d",index);
	auto pos = GAME_DATA_POINT(pos_name);
	if (_hair)
	{
		this->removeChild(_hair);
		_hair = _hairs.at(index);
		this->addChild(_hair,2);
	}
	else
	{
		_body->setSpriteFrame(GAME_DATA_STRING("toy_doll_empty"));
		_hair = _hairs.at(index);
		this->addChild(_hair,2);
	}
	_hair->setPosition(pos);
}

void ToyDoll::changeCloth(int index)
{
    if (_toyAnimate) {
        return;
    }
    _toyAnimate = true;
	auto pos_name = StringUtils::format("toy_doll_cloth_pos_%d",index);
    auto progressTo1 = ProgressTo::create(1, 100);

    _emitter->setVisible(true);
	auto pos = GAME_DATA_POINT(pos_name);
	if (_cloth)
	{
        if (_cloth == _clothes.at(index))
        {
            return;
        }
//		this->removeChild(_cloth);
//		_cloth = _clothes.at(index);
//		this->addChild(_cloth,1);

        auto cloth = _clothes.at(index);
        cloth->setPosition(pos);
        cloth->setLocalZOrder(_cloth->getLocalZOrder()+1);
        this->addChild(cloth);
        auto progressTo2 = ProgressTo::create(1, 0);
        _cloth->setMidpoint(Vec2(0,0));
        _cloth->runAction(progressTo2);
        cloth->runAction(Sequence::create(progressTo1,CallFunc::create([=](){
            _cloth->setPercentage(0);
            this->removeChild(_cloth);
            _cloth->setMidpoint(Vec2(0,1));
            _cloth = cloth;
            _toyAnimate = false;
        }), NULL));
	}
	else
	{
		_cloth = _clothes.at(index);
		this->addChild(_cloth,1);
        _cloth->runAction(progressTo1);
        _cloth->setPosition(pos);

	}
    _emitter->runAction(Sequence::create(MoveBy::create(1, Vec2(0,-462)),CallFunc::create([=](){
        _emitter->setPosition(-60,190);
        _emitter->setVisible(false);
        _toyAnimate = false;
    }),NULL));

}