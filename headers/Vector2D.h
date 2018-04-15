#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

struct Vector2D {
    Vector2D() :
	x(0),
	y(0)
    {}

    Vector2D(int xVal, int yVal) :
	x(xVal),
	y(yVal)
    {}

    int x;
    int y;
}

#endif
