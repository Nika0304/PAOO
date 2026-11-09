#include "point.h"

GoodPoint::GoodPoint() : x(0), y(0)
{
}

GoodPoint::GoodPoint(int px, int py) : x(px), y(py)
{
}

int GoodPoint::getX() const
{
    return x;
}

int GoodPoint::getY() const
{
    return y;
}
