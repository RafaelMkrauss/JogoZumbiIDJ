#include "Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0) {}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Vec2 Rect::Center() const {
    return Vec2(x + w / 2, y + h / 2);
}

float Rect::Distance(Rect other) const {
    return Center().Distance(other.Center());
}

bool Rect::Contains(Vec2 point) const {
    return point.x >= x && point.x <= x + w &&
           point.y >= y && point.y <= y + h;
}

Rect Rect::operator+(Vec2 offset) const {
    return Rect(x + offset.x, y + offset.y, w, h);
}

Rect& Rect::operator+=(Vec2 offset) {
    x += offset.x;
    y += offset.y;
    return *this;
}
