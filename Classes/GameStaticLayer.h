#pragma once
#include "BaseLayer.h"
#include "Shelf.h"
#include "PopToy.h"
#include "BaseToy.h"

class GameStaticLayer :public BaseLayer
{
public:
	GameStaticLayer();
	~GameStaticLayer();

	CREATE_FUNC(GameStaticLayer);
	virtual bool init();
    CC_SYNTHESIZE(bool,_shouldDrawerTouched,ShouldDrawerTouched);
    void onDrawerTouched(Vec2 position);
    
    void openDrawer(Vec2 position);
    void PopToy(ToyType type);
private:
    Shelf *_shelf;
    class PopToy *_popToy;
};