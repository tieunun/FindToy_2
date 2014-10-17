#include "Shelf.h"
#include "GameStaticLayer.h"

Shelf::Shelf()
{

}

Shelf::~Shelf()
{

}

void Shelf::onEnter()
{
	BaseNode::onEnter();
	if (_onEnterCount >1)
	{
		return;
	}
	auto str = GAME_DATA_STRING("shelf");
	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("shelf"));
	this->addChild(_body);
	auto shelfSize = _body->getContentSize();
	this->setContentSize(shelfSize);

	auto bodySize = GAME_DATA_SIZE("shelf_size");  //how many in horizen,how many in vetical
	auto drawerSize = GAME_DATA_SIZE("drawer_size");
	auto startPos = GAME_DATA_POINT("drawer_start_pos");

	//picture can not fit ,so we user offset
	float xOffset = 0;   
	float yOffset = 0;
	for (int i = 0;i < bodySize.height; i ++ )
	{
		for (int j = 0 ; j < bodySize.width ; j++)
		{
			if (j==3)
			{
				xOffset +=2;
			}
			auto drawer = Drawer::create();
            drawer->setDrawerPosition(Vec2(j,i));
			drawer->setPosition(startPos+Vec2(drawerSize.width*j,drawerSize.height*i)+Vec2(xOffset,yOffset));
			_body->addChild(drawer);
			_drawers.pushBack(drawer);
			xOffset +=1;
			
		}
		xOffset = 0;
		yOffset +=.5f;
	}
}

void Shelf::onDrawerTouched(cocos2d::Vec2 position)
{
    auto layer = (GameStaticLayer *)this->getParent();
    layer->onDrawerTouched(position);
}