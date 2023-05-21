#pragma once

class Vector2 {
public:
    Vector2() = default;

    constexpr Vector2(int x, int y)
        :
        x(x),
        y(y) {}

    int x;
    int y;

    const Vector2& operator=(const Vector2& rhs) {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    constexpr bool operator==(const Vector2& rhs) const {
        return (x == rhs.x && y == rhs.y);
    }
    constexpr bool operator!=(const Vector2& rhs) const {
        return !(*this == rhs);
    }

    constexpr bool operator==(const int rhs) const {
        return (x == rhs && y == rhs);
    }
    constexpr bool operator!=(const int rhs) const {
        return !(*this == rhs);
    }

    constexpr Vector2 operator+(const Vector2& rhs) const {
        return { x + rhs.x, y + rhs.y };
    }
    const Vector2& operator+=(const Vector2& rhs) {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    constexpr Vector2 operator-(const Vector2& rhs) const {
        return { x - rhs.x, y - rhs.y };
    }
    const Vector2& operator-=(const Vector2& rhs) {
        x -= rhs.x;
        y -= rhs.y;

        return *this;
    }
};
