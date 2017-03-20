//
// Created by 吴凡 on 2017/3/20.
//


/*
 * template<class T>
 * class DataProcessor {
 * public:
 *      double process(const T& v1, const T& v2, const T& v3);
 * };
 *
 * // optimized version for integral types
 * template<class T>
 * class DataProcessor {
 * public:
 *      typedef int fast_int_t;
 *      double process(fast_int_t v1, fast_int_t v2, fast_int_t v3);
 * };
 *
 * // optimized version for float types
 * template<class T>
 * class DataProcessor {
 * public:
 *      double process(double v1, double v2, double v3);
 * };
 *
 * ?? how to make compiler automatically choose the correct class for a specific type
 */

// SFINAE (Substitution Failure Is Not An Error)
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <iostream>

template<class T, class Enable = void>
class DataProcessor {
    // ...
public:
    double process(T& v1, T& v2, T& v3) {
        return 1.0;
    }
};

template<class T>
class DataProcessor<T, typename boost::enable_if_c<boost::is_integral<T>::value>::type> {
    // ...
public:
    typedef int fast_int_t;
    double process(fast_int_t v1, fast_int_t v2, fast_int_t v3) {
        return 2.0;
    }
};

template<class T>
class DataProcessor<T, typename boost::enable_if_c<boost::is_float<T>::value>::type> {
    // ...
public:
    double process(double v1, double v2, double v3) {
        return 3.0;
    }
};

template<class T>
double example_func(T v1, T v2, T v3) {
    DataProcessor<T> processor;
    return processor.process(v1, v2, v3);
}

int main() {
    std::string s("hello");
    std::cout << example_func(s, s, s) << "\n";
    int i = 0;
    std::cout << example_func(i, i, i) << "\n";
    double d = 0.0f;
    std::cout << example_func(d, d, d) << "\n";
    return 0;
}