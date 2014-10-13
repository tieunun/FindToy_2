#include "BaseNode.h"

class Desk :public BaseNode
{
public:
	Desk();
	~Desk();

	virtual void onEnter();
	CREATE_FUNC(Desk);
};