#include "Ladder.h"

Ladder::Ladder()
{
    _ladderPos = 0;
}

Ladder::~Ladder()
{

}

void Ladder::onEnter()
{
	BaseNode::onEnter();
	if (_onEnterCount >1)
	{
		return;
	}
	auto body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("koala_ladder"));
	this->addChild(body);
}