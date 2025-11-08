#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>


template <class T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t current_size;
    size_t max_capacity;

    void resize_array(size_t new_capacity) {
        if (new_capacity <= max_capacity) {
            return;
        }

        auto new_data = std::make_unique<T[]>(new_capacity);

        for (size_t i = 0; i < current_size; ++i) {   
            new_data[i] = std::move(data[i]);
        }

        data = std::move(new_data);
        max_capacity = new_capacity;
    }

public:
    size_t get_size() const { return current_size; }
    size_t get_capacity() const { return max_capacity; }

    Array() : current_size(0), max_capacity(8), data(std::make_unique<T[]>(8)) {}
    ~Array() = default;

    Array(const Array& other) : current_size(other.current_size), max_capacity(other.max_capacity) {
        data = std::make_unique<T[]>(max_capacity);
        for (size_t i = 0; i < current_size; ++i) {
            data[i] = other.data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            Array temp(other);
            *this = std::move(temp);
        }
        return *this;
    }

    Array(Array&& other) noexcept
        : data(std::move(other.data)), current_size(other.current_size), max_capacity(other.max_capacity) {
        other.current_size = 0;
        other.max_capacity = 0;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            current_size = other.current_size;
            max_capacity = other.max_capacity;

            other.current_size = 0;
            other.max_capacity = 0;
        }
        return *this;
    }

    void add_element(T&& element) {
        if (current_size >= max_capacity) {
            resize_array(max_capacity * 2);
        }
        data[current_size++] = std::move(element);
    }

    void remove_element(size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Индекс за пределами массива");
        }
        for (size_t i = index; i < current_size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --current_size;
    }

    T& get_element(size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Индекс за пределами массива");
        }
        return data[index];
    }

    const T& get_element(size_t index) const {
        if (index >= current_size) {
            throw std::out_of_range("Индекс за пределами массива");
        }
        return data[index];
    }

    double calculate_total_area() const {
        double total_area = 0.0;
        for (size_t i = 0; i < current_size; ++i) {
            total_area += static_cast<double>(*data[i]);
        }
        return total_area;
    }

    template <typename FigureType>
    void read_figure_from_input() {
        std::shared_ptr<FigureType> new_figure = std::make_shared<FigureType>();
        std::cin >> *new_figure;
        add_element(std::move(new_figure));
    }

    class Iterator {
    private:
        T* current_ptr;
    public:
        Iterator(T* ptr) : current_ptr(ptr) {}
        T& operator*() { return *current_ptr; }
        Iterator& operator++() { ++current_ptr; return *this; }
        bool operator!=(const Iterator& other) const { return current_ptr != other.current_ptr; }
    };

    Iterator begin() { return Iterator(data.get()); }
    Iterator end() { return Iterator(data.get() + current_size); }

    friend std::ostream& operator<<(std::ostream& os, const Array& array) {
        os << "Массив фигур (размер: " << array.current_size << ", вместимость: " << array.max_capacity << ")" << std::endl;
        for (size_t i = 0; i < array.current_size; ++i) {
            os << "[Фигура №" << i << "]: " << *array.data[i] << std::endl;
        }
        return os;
    }
};