#pragma once
#include "BaseLayer.h"
#include "BaseToy.h"

class PlayToyBackground :public BaseLayer
{
public:
	PlayToyBackground();
	~PlayToyBackground();

	virtual bool init();
	static PlayToyBackground *create(ToyType toyType);
	void move();
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    void onDraw(const Mat4 &transform, bool transformUpdated);
private:
	ToyType _type;
    std::vector<Rect> _rects;
    CustomCommand _customCommand;

};