#include "Ladder.h"

Ladder::Ladder()
{

}

Ladder::~Ladder()
{

}

void Ladder::onEnter()
{
	BaseNode::onEnter();

	auto body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("koala_ladder"));
	this->addChild(body);
}