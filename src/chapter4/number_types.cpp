//
// Created by 吴凡 on 2017/3/20.
//

/*
 * template<class T>
 * T process(const T& val) {
 *   //...
 * }
 * how to optimize for size 1, 4, 8
 */

#include <boost/mpl/or.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <iostream>

namespace detail {

template<class T, class Tag>
T process_impl(const T& val, Tag /*ignored*/) {
    // ...
    std::cout << "Generic\n";
    return val;
}

template<class T>
T process_impl(const T& val, boost::mpl::int_<1> /*ignored*/) {
    std::cout << "Optimize for 1\n";
    return val;
}

template<class T>
T process_impl(const T& val, boost::mpl::int_<4>) {
    std::cout << "Optimize for 4\n";
    return val;
}

template<class T>
T process_impl(const T& val, boost::mpl::int_<8>) {
    std::cout << "Optimize for 8\n";
    return val;
}

}

template<class T>
T process(const T& val) {
    BOOST_STATIC_ASSERT(boost::is_pod<T>::value);
    return detail::process_impl(val, boost::mpl::int_<sizeof(T)>());
}

int main() {
    char c = 10;
    process(c);

    int i = 10;
    process(i);

    int64_t l = 10;
    process(l);

    //std::string s("Hello");
    //process(s);
    short sh = 10;
    process(sh);
    return 0;
}


