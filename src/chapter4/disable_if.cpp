//
// Created by 吴凡 on 2017/3/20.
//


/*
 * we had a template function that works with all available types
 *
 * template<class T>
 * T process_data(const T& t1, const T& t2, const T& t3);
 *
 * Now that we write code using process_data.
 * Later we optimized process_data function for types that support operator +=.
 *
 * template<class T>
 * T process_data_plus_assign(const T& t1, const T& t2, const T& t3);
 *
 * But we don't want to change the already written code.
 *
 * ?? How
 */

#include <boost/type_traits/has_plus_assign.hpp>
#include <boost/utility/enable_if.hpp>
#include <iostream>

template<class T>
T process_data_plus_assign(const T& t1, const T& t2, const T& t3);

template<class T>
typename boost::disable_if_c<boost::has_plus_assign<T>::value, T>::type process_data(const T& t1, const T& t2, const T& t3) {
    std::cout << "disable process_data" << "\n";
    return t1 + t2 + t3;
}

template<class T>
typename boost::enable_if_c<boost::has_plus_assign<T>::value, T>::type process_data(const T& t1, const T& t2, const T& t3) {
    std::cout << "process_data" << "\n";
    return process_data_plus_assign(t1, t2, t3);
}

template<class T>
T process_data_plus_assign(const T& t1, const T& t2, const T& t3) {
    std::cout << "process_data_plus_assign" << "\n";
    return t1 + t2 + t3;
}

template<class T>
T example_process(const T& t1, const T& t2, const T& t3) {
    return process_data(t1, t2, t3);
}

class C {
public:
    C(int i = 0):i_{i}{}
    int get() const {
        return i_;
    }
private:
    int i_;
};

C operator+(const C& c1, const C& c2) {
    return C(c1.get() + c2.get());
}

std::ostream& operator<<(std::ostream& out, const C& c) {
    out << c.get();
    return out;
}

int main() {
    int i = 1;
    std::cout << example_process(i, i, i) << "\n";
    C c(1);
    std::cout << example_process(c, c, c) << "\n";
}
