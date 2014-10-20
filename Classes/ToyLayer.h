#pragma once
#include "BaseLayer.h"
#include "BaseToy.h"
#include "Koala.h"
#include "Koala_.h"
class ToyLayer :
	public BaseLayer
{
public:
	ToyLayer(void);
	~ToyLayer(void);

	virtual bool init();
    CREATE_FUNC(ToyLayer);
    void moveKoala(Vec2 position);
	void checkAnyToyInPosition(Vec2 position);
	void putOnToy();
	void setShouldDrawerTouched(bool touched);
    virtual void onEnter();
    void openDrawer(Vec2 position);
    void handInToy(ToyType type);						//order kaola find the way
	void handIn(ToyType type);							//koala notify this to hand in toy
private:

	void initPutOnPositions();


	Vector<BaseToy*> _putOnToies;
	std::vector<Vec2> _putOnPositions;
	std::vector<Vec2> _toyPositions;

	Vector<BaseToy*> _toies;
	Koala_ *_koala;
};

