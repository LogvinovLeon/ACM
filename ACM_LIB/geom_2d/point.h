#pragma once

#include "../defines.h"

template<class T>
struct Point {
    T x, y;

    Point(T x = 0, T y = 0) : x(x), y(y) { }
    Point(std::initializer_list<T> coord) : Point(*coord.begin(), *(coord.begin() + 1)) {
        assert(coord.size() == 2);
    }

    friend istream &operator>>(istream &is, Point &p) { return is >> p.x >> p.y; }
    friend ostream &operator<<(ostream &os, const Point &p) { return os << p.x << " " << p.y; }

    Point operator+(Point a) { return Point(x + a.x, y + a.y); }
    Point operator+=(Point a) { return *this = *this + a; }
    Point operator-(Point a) { return Point(x - a.x, y - a.y); }
    Point operator-=(Point a) { return *this = *this - a; }
    Point operator-() { return Point(-x, -y); }
    Point operator*(T a) { return Point(x * a, y * a); }
    Point operator*=(T a) { return *this = *this * a; }
    Point operator/(T a) { return Point(x / a, y / a); }
    Point operator/=(T a) { return *this = *this / a; }
    // |a|*|b|*cos(alpha)
    T operator*(Point a) { return x * a.x + y * a.y; }
    // cross product
    T operator%(Point a) { return x * a.y - y * a.x; }
    FT len() {
        return sqrtl(*this * *this);
    }
    Point withLen(FT l) {
        return (*this * (l / len()));
    }
    bool cw(Point a);
    bool ccw(Point a);
};

template<>
bool Point<FT>::cw(Point<FT> a) { return *this % a < -eps; }
template<>
bool Point<FT>::ccw(Point<FT> a) { return *this % a > eps; }
template<>
bool Point<IT>::cw(Point<IT> a) { return *this % a < 0; }
template<>
bool Point<IT>::ccw(Point<IT> a) { return *this % a > 0; }
