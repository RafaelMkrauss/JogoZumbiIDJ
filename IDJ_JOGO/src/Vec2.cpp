#include "Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

float Vec2::Magnitude() const {
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::Normalized() const {
    float mag = Magnitude();
    if (mag == 0) {
        return Vec2(0, 0);
    }
    return Vec2(x / mag, y / mag);
}

float Vec2::Distance(Vec2 other) const {
    return (*this - other).Magnitude();
}

float Vec2::Angle() const {
    return std::atan2(y, x);
}

Vec2 Vec2::Rotate(float angleRad) const {
    float cosA = std::cos(angleRad);
    float sinA = std::sin(angleRad);
    return Vec2(x * cosA - y * sinA, y * cosA + x * sinA);
}

Vec2 Vec2::operator+(Vec2 other) const {
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(Vec2 other) const {
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

Vec2& Vec2::operator+=(Vec2 other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(Vec2 other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2& Vec2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}
