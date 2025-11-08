#pragma once

#include "pentagon.h"
#include "hexagon.h"
#include "octagon.h"


template <Scalar T>
class FigureFactory {
public:
    static std::shared_ptr<Figure<T>> create_figure(FigureType type) {
        switch(type) {
            case FigureType::PENTAGON: 
                return std::make_shared<Pentagon<T>>();
            case FigureType::HEXAGON: 
                return std::make_shared<Hexagon<T>>();
            case FigureType::OCTAGON: 
                return std::make_shared<Octagon<T>>();
            default: 
                throw std::invalid_argument("Неизвестный тип фигуры");
        }
    }
    static std::string get_figure_name(FigureType type) {
        switch(type) {
            case FigureType::PENTAGON: return "пятиугольник";
            case FigureType::HEXAGON: return "шестиугольник";
            case FigureType::OCTAGON: return "восьмиугольник";
            default: return "неизвестная фигура";
        }
    }
};