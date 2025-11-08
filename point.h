#pragma once

#include <type_traits>
#include <memory>
#include <iostream>
#include <concepts>
#include <cmath>


template <typename T>
concept Scalar = std::is_scalar<T>::value;

template <Scalar T>
class Point {
public:
    T x;
    T y;

    Point() : x(T()), y(T()) {}
    Point(T x_val, T y_val) : x(x_val), y(y_val) {}

    bool operator==(const Point<T>& other) const {
        return std::abs(x - other.x) < 1e-10 && std::abs(y - other.y) < 1e-10;
    }

    double distance_to(const Point<T>& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    Point<T> rotate(double angle) const {
        return Point<T>(
            x * std::cos(angle) - y * std::sin(angle),
            x * std::sin(angle) + y * std::cos(angle)
        );
    }

    friend std::istream& operator>>(std::istream& is, Point<T>& point) {
        is >> point.x >> point.y;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
};