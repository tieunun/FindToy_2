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
private:
	Vector<BaseToy*> _toies;
	std::vector<Vec2> _toyPositions;
	Koala *_koala;
};

