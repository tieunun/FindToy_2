#include "BaseLayer.h"
#include "BaseToy.h"

class PlayToyPlayLayer :public BaseLayer
{
public:
	PlayToyPlayLayer();
	~PlayToyPlayLayer();

	virtual bool init();
	static PlayToyPlayLayer *create(ToyType toyType);
	CC_PROPERTY(ToyType,_type,Type);
private:
	BaseToy *_toy;
};