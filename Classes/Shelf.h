#include "BaseNode.h"
#include "Drawer.h"

class Shelf:public BaseNode
{
public:
	Shelf();
	~Shelf();

	CREATE_FUNC(Shelf);
	virtual void onEnter();

private:
	Sprite *_body;
	Vector<Drawer*> _drawers;
};