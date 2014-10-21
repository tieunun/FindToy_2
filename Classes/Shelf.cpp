#include "Shelf.h"
#include "GameStaticLayer.h"
#include "GameConfigure.h"
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
	
	auto bg = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("drawer_bg"));
	this->addChild(bg);

	auto bodySize = GAME_DATA_SIZE("shelf_size");  //how many in horizen,how many in vetical
	auto drawerSize = GAME_DATA_SIZE("drawer_size");
	auto startPos = GAME_DATA_POINT("drawer_start_pos")-Vec2(390,258);

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
            drawer->setDrawerPosition(Vec2(j,i));           //set up the relative position in shelf like (1,1),(0,1)
			drawer->setPosition(startPos+Vec2(drawerSize.width*j,drawerSize.height*i)+Vec2(xOffset,yOffset));
			this->addChild(drawer);
			_drawers.pushBack(drawer);
			xOffset +=1;
			
		}
		xOffset = 0;
		yOffset +=1.0f;
	}

	auto str = GAME_DATA_STRING("shelf");
	_body = Sprite::createWithSpriteFrameName(GAME_DATA_STRING("shelf"));
	this->addChild(_body);
	auto shelfSize = _body->getContentSize();
	this->setContentSize(shelfSize);
    
    auto toyPos = GameConfigure::getInstance()->getToyPosition();
    int index = 0;
    for(auto pos : toyPos)
    {
        auto drawer = _drawers.at(pos.x+pos.y*4);
        drawer->setToyType((ToyType)index++);
    }


}

void Shelf::onDrawerTouched(cocos2d::Vec2 position)
{
    auto layer = (GameStaticLayer *)this->getParent();
    layer->onDrawerTouched(position);
}

void Shelf::openDrawer(Vec2 position)
{
    auto drawer = _drawers.at(position.x+position.y*4);
    auto type = drawer->getToyType();
	drawer->open();
    auto layer = (GameStaticLayer *)this->getParent();
    layer->PopToy(type);
}