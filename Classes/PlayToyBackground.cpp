#include "PlayToyBackground.h"
#include "ToyPistol.h"
#include "ToyHarmonica.h"
#include "ClothShelf.h"
#include "ToyHelicopter.h"
#include "PlayToyScene.h"

PlayToyBackground::PlayToyBackground()
{

}

PlayToyBackground::~PlayToyBackground()
{

}

PlayToyBackground *PlayToyBackground::create(ToyType toyType)
{
	auto layer = new PlayToyBackground();
	layer->_type = toyType;
	layer->init();
	layer->autorelease();
	return layer;
}

bool PlayToyBackground::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	auto bgName = GAME_DATA_STRING("toy_background_type");
	auto bgStr  = StringUtils::format(bgName.c_str(),_type);
	auto bg_frame_name = GAME_DATA_STRING(bgStr);
	auto bg = Sprite::createWithSpriteFrameName(bg_frame_name);
	bg->setPosition(_winSize/2);
	this->addChild(bg);
	switch (_type)
	{
	case k_toy_harmonica:
		break;
	case k_toy_doll:
		{
			auto clothShelf = ClothShelf::create();
			clothShelf->setPosition(-322,-29);
			this->addChild(clothShelf);
		}
		break;
	case k_toy_helicopter:
		{
			this->removeAllChildren();
			auto bg1 = Sprite::create("toy_background_6.jpg");
			bg1->setAnchorPoint(Vec2(0,0));
			this->addChild(bg1,0,11);
			auto bg2 = Sprite::create("toy_helicopter_grass.png");
			bg2->setAnchorPoint(Vec2(0,0));
			this->addChild(bg2);
			auto bg3 = Sprite::create("toy_helicopter_block_0.png");
			bg3->setAnchorPoint(Vec2(0,0));
			this->addChild(bg3);
			auto bg4 = Sprite::create("toy_helicopter_block_1.png");
			bg4->setPosition(1709,559);
			this->addChild(bg4);
            for ( int i = 0;i<12;i++)
            {
                auto rect_name = StringUtils::format("toy_helicopter_rect_%d",i);
                _rects.push_back(GAME_DATA_RECT(rect_name));                
            }
		}
		break;
	default:
		break;
	}

	return true;
}

void PlayToyBackground::move()
{
	auto bg = this->getChildByTag(11);
	auto size = bg->getContentSize();
	auto moveH = MoveBy::create((size.width-_winSize.width)/Toy_Helicopter_H_Speed,Vec2(-(size.width-_winSize.width),0));
	moveH ->setTag(11);
	this->runAction(Sequence::create(moveH,CallFunc::create([=](){
		auto scene = (PlayToyScene*)this->getParent();
		scene->moveHelicopter();
	}),NULL));
}

void PlayToyBackground::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _customCommand.init(10);
    _customCommand.func = CC_CALLBACK_0(PlayToyBackground::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void PlayToyBackground::onDraw(const cocos2d::Mat4 &transform, bool transformUpdated)
{
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    glLineWidth( 2.0f );
    DrawPrimitives::setDrawColor4B(255,0,0,255);
    
   for(auto rect:_rects)
   {
       DrawPrimitives::drawRect(rect.origin, rect.origin+rect.size);
       
   }
//    DrawPrimitives::drawRect(_rects[0].origin, _rects[0].origin+_rects[0].size);
//    DrawPrimitives::drawRect(Vec2(-178,68), Vec2(174,36));
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}