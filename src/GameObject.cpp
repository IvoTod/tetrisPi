#include "GameObject.h"
#ifndef __TFT_ST7735__
#define __TFT_ST7735__
#include <tft_st7735.h>
#endif

GameObject::GameObject() :
    pos(Vector2D())
{}

GameObject::GameObject(int x, int y) :
    pos(Vector2D(x, y))
{}

GameObject::GameObject(Vector2D position) :
    pos(position)
{}

void GameObject::draw(TFT_ST7735& tft) {}

void GameObject::setPosition(Vector2D newPos) {
    pos.x = newPos.x;
    pos.y = newPos.y;
}

Vector2D GameObject::getPosition() {
    return pos;
}
