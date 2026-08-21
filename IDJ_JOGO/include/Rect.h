#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);

    Vec2 Center() const;
    float Distance(Rect other) const;

    bool Contains(Vec2 point) const;

    Rect operator+(Vec2 offset) const;
    Rect& operator+=(Vec2 offset);
};

#endif
