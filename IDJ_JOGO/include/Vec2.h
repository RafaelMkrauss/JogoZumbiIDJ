#ifndef VEC2_H
#define VEC2_H

class Vec2 {
public:
    float x, y;

    Vec2();
    Vec2(float x, float y);

    float Magnitude() const;
    Vec2 Normalized() const;

    float Distance(Vec2 other) const;
    float Angle() const;

    Vec2 Rotate(float angleRad) const;

    Vec2 operator+(Vec2 other) const;
    Vec2 operator-(Vec2 other) const;
    Vec2 operator*(float scalar) const;

    Vec2& operator+=(Vec2 other);
    Vec2& operator-=(Vec2 other);
    Vec2& operator*=(float scalar);
};

#endif
