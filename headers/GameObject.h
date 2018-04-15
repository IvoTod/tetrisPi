#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "Vector2D.h"
class TFT_ST7735;

class GameObject {
    public:
	GameObject();
	GameObject(int x, int y);
	GameObject(Vector2D position);
	virtual void update(int ms)=0;
	virtual void draw(TFT_ST7735& tft);
	void setPosition(Vector2D newPos);
	Vector2D getPosition();
    protected:
	Vector2D pos;
	
};

#endif
