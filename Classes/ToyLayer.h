#pragma once
#include "BaseLayer.h"
#include "BaseToy.h"
#include "Koala.h"
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
private:

	void initPutOnPositions();
	Vector<BaseToy*> _toies;
	Vector<BaseToy*> _putOnToies;
	std::vector<Vec2> _putOnPositions;
	std::vector<Vec2> _toyPositions;
	Koala *_koala;
};

