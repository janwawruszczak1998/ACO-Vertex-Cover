//
// Created by Jan on 2021-10-11.
//

#ifndef AOIN_POINT_H
#define AOIN_POINT_H

#include <type_traits>


template<typename T>
class Point {
public:
    Point(T x_, T y_) : x(x_), y(y_) {

    }



    bool equals(T const& x_, T const& y_, std::true_type) const {
        return x_ - y_ < 0.01;
    }

    bool equals(T const& x_, T const& y_, std::false_type) const {
        return x_ == y_;
    }

    bool equals(T const& x_, T const& y_, std::conditional_t<std::is_floating_point<T>::value, std::true_type, std::false_type>* = nullptr) const {
        return equals(x_, y_);
    }

    bool operator==(Point<T> const& compare_point) const {
        return equals(compare_point.get_x(), compare_point.get_y());
    }

    decltype(auto) calculate_distance(T const& x_, T const& y_) const {
        return sqrt((x - x_) * (x - x_) + (y - y_) * (y - y_));
    }

    T get_x() const {
        return x;
    }

    T get_y() const {
        return y;
    }

private:
    T x, y;
};


#endif //AOIN_POINT_H