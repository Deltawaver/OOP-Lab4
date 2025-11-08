#include "gtest/gtest.h"
#include <iostream>
#include <memory>
#include <cmath>
#include <sstream>

#include "point.h"
#include "figure.h"
#include "pentagon.h"
#include "hexagon.h"
#include "octagon.h"
#include "array.h"

using FigurePtr = std::shared_ptr<Figure<double>>;

FigurePtr create_test_pentagon() {
    return std::make_shared<Pentagon<double>>(
        Point<double>(0.0, 2.0),
        Point<double>(1.9021, 0.6180),
        Point<double>(1.1756, -1.6180),
        Point<double>(-1.1756, -1.6180),
        Point<double>(-1.9021, 0.6180)
    );
}

FigurePtr create_test_hexagon() {
    double side = 1.5;
    double height = side * std::sqrt(3.0);
    
    return std::make_shared<Hexagon<double>>(
        Point<double>(-side, 0.0),
        Point<double>(-side/2, height),
        Point<double>(side/2, height),
        Point<double>(side, 0.0),
        Point<double>(side/2, -height),
        Point<double>(-side/2, -height)
    );
}

FigurePtr create_test_octagon() {
    double a = 1.0;
    double k = 1.0 + std::sqrt(2.0);
    
    return std::make_shared<Octagon<double>>(
        Point<double>(0.0, k),
        Point<double>(a/std::sqrt(2.0), a/std::sqrt(2.0)),
        Point<double>(k, 0.0),
        Point<double>(a/std::sqrt(2.0), -a/std::sqrt(2.0)),
        Point<double>(0.0, -k),
        Point<double>(-a/std::sqrt(2.0), -a/std::sqrt(2.0)),
        Point<double>(-k, 0.0),
        Point<double>(-a/std::sqrt(2.0), a/std::sqrt(2.0))
    );
}

TEST(PointTest, BasicOutput) {
    Point<int> p(5, 10);
    std::stringstream ss;
    ss << p;
    ASSERT_EQ(ss.str(), "(5, 10)");
}

TEST(FigureTest, PentagonArea) {
    FigurePtr pent = create_test_pentagon();
    ASSERT_NEAR(pent->calculate_area(), 9.5106, 1e-3);
}

TEST(FigureTest, HexagonArea) {
    FigurePtr hex = create_test_hexagon();
    ASSERT_NEAR(hex->calculate_area(), 11.6913, 1e-3);
}

TEST(FigureTest, OctagonArea) {
    FigurePtr oct = create_test_octagon();
    ASSERT_NEAR(oct->calculate_area(), 4.8284, 1e-3);
}

TEST(ArrayTest, TotalArea) {
    Array<FigurePtr> arr;
    arr.add_element(create_test_pentagon());
    arr.add_element(create_test_hexagon());
    ASSERT_NEAR(arr.calculate_total_area(), 21.2019, 1e-3);
    ASSERT_EQ(arr.get_size(), 2);
}

TEST(ArrayTest, MoveOperations) {
    Array<FigurePtr> arr1;
    arr1.add_element(create_test_pentagon());
    arr1.add_element(create_test_hexagon());
    
    Array<FigurePtr> arr2 = std::move(arr1);
    ASSERT_EQ(arr1.get_size(), 0);
    ASSERT_EQ(arr2.get_size(), 2);
}

TEST(ArrayTest, RemoveElement) {
    Array<FigurePtr> arr;
    arr.add_element(create_test_pentagon());
    arr.add_element(create_test_hexagon());
    arr.add_element(create_test_octagon());
    
    arr.remove_element(1);
    ASSERT_EQ(arr.get_size(), 2);
    ASSERT_NEAR(arr.calculate_total_area(), 14.3390, 1e-3);
}