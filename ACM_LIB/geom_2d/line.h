#pragma once

#include "point.h"

template<class T>
struct Line {
    T A, B, C;
    Line(T A = 0, T B = 0, T C = 0) : A(A), B(B), C(C) { }
    Line(Point<T> p, Point<T> q) {
        A = p.y - q.y;
        B = q.x - p.x;
        C = -A * p.x - B * p.y;
        norm();
    }
    Line(std::initializer_list<Point<T>> points) : Line(*points.begin(), *(points.begin() + 1)) {
        assert(points.size() == 2);
    }
    void norm();
    Point<T> normal() {
        return {A, B};
    }
    T distance(Point<T> a);
    T distanceSigned(Point<T> a);
    Point<T> reflect(Point<T> p) {
        return p - normal().withLen(distanceSigned(p)) * 2;
    }
    friend istream &operator>>(istream &is, Line &l) {
        Point<T> p, q;
        is >> p >> q;
        l = Line(p, q);
        return is;
    }
    friend ostream &operator<<(ostream &os, Line &l) { return os << l.A << " " << l.B << " " << l.C; }
};

template<>
void Line<IT>::norm() {
    IT gcd = __gcd(__gcd(A, B), C);
    A /= gcd, B /= gcd, C /= gcd;
    if (A < 0 ||
        A == 0 && B < 0 ||
        A == 0 && B == 0 && C < 0)
        A *= -1, B *= -1, C *= -1;
}

template<>
void Line<FT>::norm() {
    FT len = sqrtl(A * A + B * B);
    A /= len, B /= len, C /= len;
    if (A < eps ||
        abs(A) < eps && B < eps ||
        abs(A) < eps && abs(B) < eps && C < eps)
        A *= -1, B *= -1, C *= -1;
}

template<>
FT Line<FT>::distance(Point<FT> a) {
    return abs(distanceSigned(a));
}
template<>
FT Line<FT>::distanceSigned(Point<FT> a) {
    return A * a.x + B * a.y + C;
}
