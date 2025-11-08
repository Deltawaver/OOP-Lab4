#pragma once

#include <iostream>
#include "figure.h"
#include <cmath>
#include <memory>
#include <typeinfo>


template <Scalar T>
class Hexagon : public Figure<T> {
public:
    Hexagon() : Figure<T>(6, nullptr, FigureType::HEXAGON) {
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(6);
        for (size_t i = 0; i < 6; ++i) {
            this->points[i] = std::make_unique<Point<T>>();
        }
        this->point_count = 6;
    }

    Hexagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, 
            const Point<T>& p4, const Point<T>& p5, const Point<T>& p6) 
            : Figure<T>(6, nullptr, FigureType::HEXAGON) {
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(6);
        this->points[0] = std::make_unique<Point<T>>(p1);
        this->points[1] = std::make_unique<Point<T>>(p2);
        this->points[2] = std::make_unique<Point<T>>(p3);
        this->points[3] = std::make_unique<Point<T>>(p4);
        this->points[4] = std::make_unique<Point<T>>(p5);
        this->points[5] = std::make_unique<Point<T>>(p6);
        this->point_count = 6;
    }

    Point<T> calculate_center() const override {
        T center_x = 0;
        T center_y = 0;

        for (size_t i = 0; i < 6; ++i) {
            center_x += this->points[i]->x;
            center_y += this->points[i]->y;
        }

        return Point<T>(center_x / static_cast<T>(6), center_y / static_cast<T>(6));
    }

    double calculate_area() const override {
        double area = 0.0;
        for (size_t i = 0; i < 6; ++i) {
            size_t j = (i + 1) % 6;
            area += this->points[i]->x * this->points[j]->y - 
                    this->points[j]->x * this->points[i]->y;
        }
        return std::abs(area) / 2.0;
    }

    bool is_valid() const override {
        if (!Figure<T>::is_valid()) return false;
        
        double first_side = this->points[0]->distance_to(*this->points[1]);

        for (size_t i = 1; i < 6; ++i) {
            size_t j = (i + 1) % 6;
            double side = this->points[i]->distance_to(*this->points[j]);
            if (std::abs(side - first_side) > 1e-6) return false;
        }
        return true;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Hexagon<T>>(*this->points[0], *this->points[1], *this->points[2], *this->points[3], *this->points[4], *this->points[5]);
    }

    bool operator==(const Figure<T>& other) const override {
        if (typeid(*this) != typeid(other)) {
            return false;
        }
        const Hexagon<T>* other_figure = dynamic_cast<const Hexagon<T>*>(&other);
        if (!other_figure) {
            return false;
        } 
        for (size_t i = 0; i < 6; ++i) {
            if (!(*this->points[i] == *other_figure->points[i])) {
                return false;
            }
        }
        return true;
    }

    void read(std::istream& input_stream) override {
        for (size_t i = 0; i < 6; ++i) {
            input_stream >> *(this->points[i]);
        }
        
        if (!this->is_valid()) {
            throw std::invalid_argument("Точки не образуют правильный шестиугольник");
        }
    }

    void print(std::ostream& output_stream) const override {
        output_stream << "Шестиугольник ";
        output_stream << "Центр: " << calculate_center() << ", площадь: " << calculate_area() << ", точки:";
        this->print_points(output_stream);
    }
};